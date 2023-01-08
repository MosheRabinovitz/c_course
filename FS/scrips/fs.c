#include "fs.h"
#include "disk.h"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

static int BIT_MAP_SIZE = 0;
static int * bitmap = NULL;


/* 
	case 1: first initialize:
			Writes the superblock.

	case 2: Creates a new filesystem on the disk:
		Destroying any data already present in the disk.

	case 3: disk already mounted:
		The disk should do nothing and return failure.
*/
int fs_format()
{
	/* case 3 */
	if (bitmap)
		return 0;


	union fs_block block;
	disk_read(0,block.data);

	/* case 2 */
	if (block.super.magic == FS_MAGIC)
	{
		int ninodeblocks = block.super.ninodeblocks;
		for (int i = 1; i <= ninodeblocks; ++i)
		{
			disk_read(i, block.data);
			for (int j = 0; j < INODES_PER_BLOCK; ++j)
				block.inode[j].isvalid = 0;
				
			disk_write(i, block.data);			
		}
		return 1;
	}
	
	/* case 1 */
	else
	{
		int n_blocks = disk_size();
		int inode_blocks = n_blocks/10 + 1;
		
		block.super.magic = FS_MAGIC;
		block.super.nblocks = n_blocks;
		block.super.ninodeblocks = inode_blocks;
		block.super.ninodes = inode_blocks * INODES_PER_BLOCK;
		
		disk_write(0,block.data);

		return 1;
	}
}


/* Scan a mounted filesystem and report on how the inodes and blocks are organized. */
void fs_debug()
{
	union fs_block block;

	/* Print the superblock data */
	disk_read(0,block.data);

	printf("\033[1;34msuperblock:\n\033[0m");
	printf("    %d blocks\n",block.super.nblocks);
	printf("    %d inode blocks\n",block.super.ninodeblocks);
	printf("    %d inodes\n",block.super.ninodes);

	/* Print the bitmap data */
	printf("\033[1;34m\nbit map:\033[0m");
	print_bitmap();
	
	/* Print the valid inodes data */
	int ninodeblocks = block.super.ninodeblocks;
	for (int i = 1; i <= ninodeblocks; ++i)
	{
		disk_read(i, block.data);
		for (int j = 0; j < INODES_PER_BLOCK; ++j)
	 	{
	 		if(block.inode[j].isvalid)
			{
				int inumber = (((i-1) * INODES_PER_BLOCK) + j);
				printf("\033[1;35minode\033[0m %d:\n", inumber);
				print_inode(inumber);
			}
		}
	}
}


/* Examine the disk for a filesystem, build a free block bitmap, and prepare the filesystem for use.
 if the disk is not formatted or the bitmap is already mounted return failure.
*/
int fs_mount()
{	
	/* The bitmap is already mounted */
	if(bitmap)
	{
		printf("\033[1;31mERROR: The bitmap is already mounted\n\033[0m");
		return 0;
	}

	union fs_block block;
	disk_read(0,block.data);

	/* If the disk is not formatted */
	if (block.super.magic != FS_MAGIC)
	{
		printf("\033[1;31mERROR: The disk is not yet formatted\n\033[0m");
		return 0;
	}

	/* Build a free block bitmap */
	BIT_MAP_SIZE = block.super.nblocks - 1 - block.super.ninodeblocks;
	bitmap = (int *) calloc(BIT_MAP_SIZE , (sizeof(int)));
	if (!bitmap)
		return 0;

	/* Update the bitmap according to the data on the disk */
	init_bitmap(block.super.ninodeblocks);
		
	return 1;
}


/* Create a new inode of zero length. On success, return the inumber. On failure, return -1. */
int fs_create()
{
	/* Finds a free inode */
	int inumber = find_empty_inode();
	if (inumber == -1)
		return -1;
	
	/* Initialize the inode data */
	struct fs_inode inode;
	inode.isvalid = 1;
	inode.size = 0;
	inode.indirect = 0;
	
	for (int i = 0; i < POINTERS_PER_INODE; ++i)
		inode.direct[i] = 0;
	
	inode_save(inumber, &inode);
	
	return inumber;
}


/* Delete the inode indicated by the inumber:
	Release all data and indirect blocks assigned to this inode and return them to the free block map.
	*/
int fs_delete( int inumber )
{
	struct fs_inode inode;
	inode_load(inumber, &inode);

	/* Checks if the inumber exists */
	if (!inode.isvalid)
	{
		printf("\033[1;31mERROR: inumber %d is not valid\n\033[0m", inumber);
		return 0;
	}

	/* Release all data if the inode is not empty */
	if(inode.size > 0)
	{
		/* free the direct data */
		for(int i = 0; i < POINTERS_PER_INODE; ++i)
			if(inode.direct[i])
			{
				free_block(inode.direct[i]);
				inode.direct[i] = 0;
			}
			else
				break;
		
		/* free the indirect data */
		if(inode.indirect)
		{
			union fs_block inblock;
			int indirect = inode.indirect;
			do {
				disk_read(indirect, inblock.data);
				
				/* free the indirect pointers */
				for(int i = 0; i < POINTERS_PER_BLOCK; ++i)
				{
					if(inblock.pointers[i])
						free_block(inblock.pointers[i]);
					
					else
						break;
				}

				free_block(indirect);

				/* Moves the indirect forward */
				indirect = inblock.pointers[POINTERS_PER_BLOCK -1];

			} while(indirect);
		}		
	}
	
	inode.size = 0;
	inode.isvalid = 0;
	inode.indirect = 0;
	
	inode_save(inumber, &inode);	
	
	return 1;
}


/* Return the logical size of the given inode, in bytes, on failure, return -1. */
int fs_getsize( int inumber )
{
	struct fs_inode inode;
	inode_load(inumber, &inode);
	
	if (!inode.isvalid)
		return -1;
	
	return inode.size;
}


/* Read data from a valid inode:
	Copy "length" bytes from the inode into the "data" pointer, starting at "offset" in the inode.
	Return the total number of bytes read.
	If the given inumber is invalid, or any other error is encountered, return 0.
	*/
int fs_read( int inumber, char *data, int length, int offset )
{
	struct fs_inode inode;
	inode_load(inumber, &inode);

	/* Checks If the given inumber is invalid */
	if(!inode.isvalid)
	{
		printf("\033[1;31mERROR: inumber %d is not valid\n\033[0m", inumber);
		return 0;
	}

	
	int read_bytes = 0; /* count the number of bytes read. */
	int end_ptr = (inode.size > offset + length) ? (offset + length) : inode.size; /* The last char to read or the last char on the file */

	while(offset < end_ptr)
	{
		/* Calculate the offset direct number and the offset index in the block data */
		int block_num = offset/DISK_BLOCK_SIZE, data_index = offset%DISK_BLOCK_SIZE, block_index;

		/* Checks if a data block exists at the direct number */
		block_index = find_the_block(&inode, block_num, 'r');
		if(block_index == -1)
			return read_bytes;

		union fs_block block;
		disk_read(block_index, block.data);

		/* Read the data block */
		int i = data_index;
		for (; i < DISK_BLOCK_SIZE && i < (end_ptr - offset); ++i)
			*data++ = block.data[i];
		
		/* Moves the offset forward and updates the read bytes */
		offset += (i - data_index);
		read_bytes+= (i - data_index);
	}
	return read_bytes;
}


/* Write data to a valid inode:
	Copy "length" bytes from the pointer "data" into the inode starting at "offset" bytes
	Return the number of bytes actually written.
	If the given inumber is invalid, or any other error is encountered, return 0.
*/
int fs_write( int inumber, const char *data, int length, int offset )
{
	struct fs_inode inode;
	inode_load(inumber, &inode);

	/* Checks If the given inumber is invalid */
	if(!inode.isvalid)
	{
		printf("\033[1;31mERROR: inumber %d is not valid\n\033[0m", inumber);
		return 0;
	}

	/* Resets the inode size on the first write */
	if (!offset)
	{
		fs_delete(inumber);
		inode_load(inumber, &inode);
		inode.isvalid = 1;
	}

	int copied_bytes = 0; /* count the number of bytes that are written. */
	int end_ptr = offset + length; /* The last char to write */

	while(offset < end_ptr)
	{
		/* Calculate the offset direct number and the offset index in the block data */
		int block_num = offset/DISK_BLOCK_SIZE, data_index = offset%DISK_BLOCK_SIZE, block_index;

		/* Checks if a data block exists at the direct number or creates a new data block to write into */
		block_index = find_the_block(&inode, block_num, 'w');
		
		/* In case the memory is full save in the inode size the number of bytes write and return */
		if(block_index == -1)
		{
			inode.size += copied_bytes;
			inode_save(inumber, &inode);
			return copied_bytes;
		}

		
		union fs_block block;
		disk_read(block_index, block.data);

		/* write into the data block */
		int i = data_index;
		for (; i < DISK_BLOCK_SIZE && i < (end_ptr - offset); ++i)
			block.data[i] = *data++;
		
		/* Moves the offset forward and updates the write bytes */
		offset += (i - data_index);
		copied_bytes += (i - data_index);

		disk_write(block_index, block.data);
	}

	/* Save in the inode size the number of bytes write and return */
	inode.size += copied_bytes;
	inode_save(inumber, &inode);
	return copied_bytes;
}


/* Update the bitmap according to the data on the disk */
void init_bitmap(int ninodeblocks)
{
	union fs_block block;
	/* Goes through all the inodes and check if thay are valid */
	for (int i = 1; i <= ninodeblocks; ++i)
	{
		disk_read(i,block.data);
		
		for(int j = 0; j < INODES_PER_BLOCK; ++j)

			/* if the inode is valid updates the bitmap with all its data blocks */
			if (block.inode[j].isvalid)
			{
				int inumber = ((i-1) * INODES_PER_BLOCK) + j;
				color_bitmap(inumber);
			}
	}
}


/* Prints all the occupied indexes */
void print_bitmap()
{
	for (int i = 0; i < BIT_MAP_SIZE; ++i)
		if (bitmap[i])
			printf("%d, ", calculate_block_index(i));
	printf("\n\n");
}


/* Free the bitmap when the disk close */
void free_bitmap()
{
	free(bitmap);
}

/* Updates the bitmap with all data blocks of the inode */
void color_bitmap(int inumber)
{
	struct fs_inode inode;
	inode_load(inumber, &inode);

	/* Updates all the data if the inode is not empty */
	if(inode.size > 0)
	{
		int i = 0, index;
		/* Updates all the direct data */
		for(; i < POINTERS_PER_INODE; ++i)
			if(inode.direct[i])
			{
				index = calculate_bitmap_index(inode.direct[i]);
				bitmap[index] = 1;
			}
			else
				break;
		
		/* Updates the indirect data */
		if(inode.indirect)
		{
			union fs_block inblock;
			int indirect = inode.indirect;
			do {
				disk_read(indirect, inblock.data);
				
				for(i = 0; i < POINTERS_PER_BLOCK; ++i)
				{
					if(inblock.pointers[i])
					{
						index = calculate_bitmap_index(inblock.pointers[i]);
						bitmap[index] = 1;
					}
					else
						break;
				}

				index = calculate_bitmap_index(indirect);
				bitmap[index] = 1;

				indirect = inblock.pointers[POINTERS_PER_BLOCK -1];
			} while(indirect);
		}		
	}
}


/* Allocate empty data block from the bitmap */
int find_empty_block()
{
	/* Return error if the bitmap is not mounted */
	if (!bitmap)
	{
		printf("\033[1;31mThe bitmap is not mounted\n\033[0m");
		return -1;
	}
	/* Search for an empty data block and color it */
	for (int i = 0; i < BIT_MAP_SIZE; ++i)
	{
		if (bitmap[i] == 0)
		{
			bitmap[i] = 1;
			return calculate_block_index(i);
		}
	}
	printf("\033[1;31mThe memory is full \n\033[0m");
	return -1;	
}


/* Release data block on the bitmap */
void free_block(int data_block_index)
{
	int i = calculate_bitmap_index(data_block_index);
	bitmap[i] = 0;
}


/* Convert the data block index on the bitmap to the data block index on the disk */
int calculate_block_index(int index)
{
	union fs_block block;
	disk_read(0,block.data);

	return (block.super.ninodeblocks + index +1);
}


/* Convert the data block index on the disk to the data block index on the bitmap */
int calculate_bitmap_index(int index)
{
	union fs_block block;
	disk_read(0,block.data);

	return (index - block.super.ninodeblocks -1);
}


/* Retuen inumber to a free inode if exsis, otherwise return -1 */
int find_empty_inode()
{
	union fs_block block;
	disk_read(0,block.data);
	
	int size = block.super.ninodeblocks;
	
	/* Run over all inodes and return if exsis empty inode */
	for (int i = 1; i <= size; ++i)
	{
		disk_read(i,block.data);
		
		for(int j = 0; j < INODES_PER_BLOCK; ++j)
			if (!block.inode[j].isvalid)
				return (((i-1) * INODES_PER_BLOCK) + j); 
	}

	printf("\033[1;31mERROR: No more valid inodes\n\033[0m");
	return -1;
}


/* Load individual inode structures by number */
void inode_load(int inumber, struct fs_inode * inode)
{
	int n = (inumber/INODES_PER_BLOCK) +1, j = inumber%INODES_PER_BLOCK;
	
	union fs_block block;
	disk_read(n,block.data);
	
	*inode = block.inode[j];
}


/* Save individual inode structures by number */
void inode_save(int inumber, struct fs_inode * inode)
{
	int n = (inumber/INODES_PER_BLOCK) +1, j = inumber%INODES_PER_BLOCK;

	union fs_block block;
	disk_read(n, block.data);
	
	block.inode[j] = *inode;
	disk_write(n, block.data);
}


/* Prints all the data of inode number */
void print_inode(int inumber)
{
	struct fs_inode inode;
	inode_load(inumber, &inode);

	/* Prints the inode size */
	printf("\033[1;32m    size:\033[0m %d \033[1;32mbytes\n\033[0m", inode.size);

	/* Prints all the direct blocks */
	printf("\033[1;32m    direct blocks: \033[0m");

	int idx = 0;
	for(; idx < POINTERS_PER_INODE; ++idx)
	if(inode.direct[idx])
		printf("%d, ", inode.direct[idx]);
	else
		break;

		
	if(inode.indirect)
	{
		union fs_block inblock;
		int indirect = inode.indirect;
		
		do {
			/* Prints the indirect blocks */
			printf("\n\033[1;32m    indirect block: \033[0m%d\n", indirect);
			printf("\033[1;32m    indirect data blocks: \033[0m");

			disk_read(indirect, inblock.data);
							
			for(idx = 0; idx < POINTERS_PER_BLOCK; ++idx)
			{
				if(inblock.pointers[idx])
					printf("%d, ", inblock.pointers[idx]);
				else
					break;
			}

			/* Moves the indirect forward */
			indirect = inblock.pointers[POINTERS_PER_BLOCK -1];

		} while(indirect);
	}
	printf("\n");
}


/* Finds in an inode the data block index for a specific direct 
	Return -1 if not found or any other error is encountered.
	if the function is called from write function creates a new data block if does'nt exsis in a specific direct 
	*/
int find_the_block(struct fs_inode * inode, int block_num, char cmd)
{
	/* Return the result if the block_num is in direct blocks */
	if (block_num < POINTERS_PER_INODE)
		if (inode->direct[block_num])
			return inode->direct[block_num];
		
		/* Allocates new data block if the data block not exsis and the cmd is 'w' */
		else if (cmd == 'w')
			return create_data_block(&(inode->direct[block_num]), 'd');

		/* If the data block not exsis and the cmd is 'r' rerturn -1 */
		else
			return -1;
	
	else
	{
	/* Return the result if the block_num is in indirect blocks */
	union fs_block inblock;
	int indirect = inode->indirect, old_direct = 0, * empty_indirect = &(inode->indirect);
	block_num -= POINTERS_PER_INODE;

	/* Moves the indirect forward if needed */
	while (block_num >= POINTERS_PER_BLOCK -1)
	{
		disk_read(indirect, inblock.data);
		old_direct = indirect;
		empty_indirect = &(inblock.pointers[POINTERS_PER_BLOCK -1]);
		indirect = inblock.pointers[POINTERS_PER_BLOCK -1];
		block_num -= POINTERS_PER_BLOCK -1;
	}
	
	/* Allocates new indirect if the new indirect not exsis and the cmd is 'w' */
	if(cmd == 'w' && !indirect)
	{
		indirect = create_data_block(empty_indirect, 'p');
		if (indirect == -1)
			return -1;
		if(old_direct)
			disk_write(old_direct, inblock.data);
	}

	disk_read(indirect, inblock.data);

	if (inblock.pointers[block_num])
		return inblock.pointers[block_num];
		
	/* Allocates new data block if the data block not exsis and the cmd is 'w' */
	else if (cmd == 'w')
	{
		int res = create_data_block(&(inblock.pointers[block_num]), 'd');
		disk_write(indirect, inblock.data);
		return res;
	}

	/* If the data block not exsis and the cmd is 'r' or any other error is encountered rerturn -1 */
	else
		return -1;
	}
}


/* Allocate a new data block if does'nt exsis in a specific direct and return the index of the block,
if the memory is full return -1 */
int create_data_block(int * direct, char cmd)
{
	/* Allocates a new data block */
	int new_block = find_empty_block();
	/* If the memory is full return -1 */
	if (new_block == -1)
			return -1;
	*direct = new_block;

	/* 	Reset the values if the block is for pointers */
	if (cmd == 'p')
	{
		union fs_block new_inblock;
		for(int i = 0; i < POINTERS_PER_BLOCK; ++i)
			new_inblock.pointers[i] = 0;
		disk_write(new_block, new_inblock.data);
	}

	return new_block;
}