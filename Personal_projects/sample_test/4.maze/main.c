#include <stdio.h>
#include "maze.h"

int main()
{
	int maze[M][N] = {
		{FREE,USED,USED,USED,USED,USED},
		{FREE,USED,USED,USED,USED,USED},
		{FREE,FREE,FREE,FREE,FREE,FREE},
		{FREE,USED,USED,FREE,USED,FREE},
		{FREE,USED,USED,FREE,USED,FREE},
		{FREE,FREE,FREE,FREE,FREE,FREE}
	};
	
	struct tile src, dst;
	src.row = 0;
	src.col = 0;

	dst.row = M-1;
	dst.col = N-3;
	
	int res = path(maze, src, dst);
	printf("res is: %d\n",res);
}
