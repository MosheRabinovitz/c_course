#include <stddef.h>
#include "disk.h"

#ifndef FS_H
#define FS_H

#define FS_MAGIC           0xf0f03410
#define INODES_PER_BLOCK   128
#define POINTERS_PER_INODE 5
#define POINTERS_PER_BLOCK 1024

struct fs_superblock {
	int magic;
	int nblocks;
	int ninodeblocks;
	int ninodes;
};

struct fs_inode {
	int isvalid;
	int size;
	int direct[POINTERS_PER_INODE];
	int indirect;
};

union fs_block {
	struct fs_superblock super;
	struct fs_inode inode[INODES_PER_BLOCK];
	int pointers[POINTERS_PER_BLOCK];
	char data[DISK_BLOCK_SIZE];
};


/* File System */
void fs_debug();
int  fs_format();
int  fs_mount();

int  fs_create();
int  fs_delete( int inumber );
int fs_getsize( int inumber );

int  fs_read( int inumber, char *data, int length, int offset );
int  fs_write( int inumber, const char *data, int length, int offset );


/* bitmap */
void init_bitmap(int ninodeblocks);
void color_bitmap(int inumber);
int find_empty_block();
void free_block(int data_block_index);
int calculate_block_index(int index);
int calculate_bitmap_index(int index);
void print_bitmap();
void free_bitmap();


/* inode blocks */
void inode_load(int inumber, struct fs_inode * inode);
void inode_save(int inumber, struct fs_inode * inode);
int find_the_block(struct fs_inode * inode, int blocknum, char cmd);
int create_data_block(int * direct, char cmd);
void print_inode(int inumber);

#endif
