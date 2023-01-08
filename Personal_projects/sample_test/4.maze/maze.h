#include <stdio.h>

#define USED -1
#define FREE 0
#define M 6
#define N 6

struct tile{
	int row;
	int col;
};


int path(int maze[M][N],struct tile src, struct tile dst);
int in_bound(struct tile t);
int used(int maze[M][N],struct tile t);


