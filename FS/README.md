# File system project

This project is the final project of c course. In the project we implemented a program that simulates a file system in Linux.

A file system includes a fixed number of blocks in memory, with the first block, a superblock, containing information about the file system, after which ten percent of the total memory blocks is allocated to the inodes table that contain information about the files - where each file is stored, what is its size, and which blocks in memory are allocated for it, followed by data blocks for the memory. In addition, in order to manage the allocation of blocks for the file system, there is a bitmap - an array the size of the number of blocks in the memory system, where the blocks currently in use by the file system are marked.

Before implementing the program, we prepared a detailed design according to the characterization of the various tasks that the program is supposed to perform, then we implemented the program:
The 'shell' file manages the communication with the user and receives from the user the various commands he wishes to execute (the 'help' command will provide the list of possible commands), the 'disk' file manages the activity with the computer's memory, and the main work in the project was done on the 'fs' file which is responsible for the communication between them and provides the computer with the tools to complete the requests that the user sends to it.

The project requirements included the writing of the following main functions (along with additional auxiliary functions):
Format – creating a file system.
Mount – boot bitmap for the system.
Debug – printing the file system data.
Create – creating a new (empty) inode.
Delete – inode deletion.
Getsize – returning the number of bytes that a specific inode (ie, a file) occupies in the file system.
Read – reading a file from a specific inode in the file system.
Write – writing a file to a specific inode in the file system.

In order to access the system, use the following format (which addresses the file system if it exists, and if not - creates a new file system):
 simplefs <file system name> <num of blocks>

 08/01/2023