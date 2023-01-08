#include <stdio.h>
#include "maze.h"

int path(int maze[M][N],struct tile src, struct tile dst)
{

	if (used(maze, src) || in_bound(src))
		return 0;
	
	if (src.row == dst.row && src.col == dst.col)
		return 1;
	
	maze[src.row][src.col] = USED;
	
	struct tile a,b,c,d;
	a.row = src.row + 1;
	a.col = src.col;
	
	b.row = src.row -1;
	b.col = src.col;
	
	c.row = src.row;
	c.col = src.col +1;
	
	d.row = src.row;
	d.col = src.col -1;
	
	int p1, p2, p3, p4;
	
	p1 = path(maze, a, dst);
	p2 = path(maze, b, dst);
	p3 = path(maze, c, dst);
	p4 = path(maze, d, dst);
	
	int res = ((p1+p2+p3+p4)>0);
	
	return res;
}


int in_bound(struct tile t)
{
	if (t.row >=M || t.row < 0)
		return 1;
	if (t.col >=N || t.col < 0)
		return 1;
	return 0;
		
}
int used(int maze[M][N],struct tile t)
{
	if (maze[t.row][t.col] == USED)
		return 1;
	return 0;
}

