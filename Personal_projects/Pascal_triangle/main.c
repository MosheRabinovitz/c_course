#include "Pascal.h"
#include <stdlib.h>
#include <stdio.h>


void main()
{
	/* Get a number as input */
	int n;
	printf("Enter number of pascal level: ");
	scanf("%d",&n);
	
	/* Initialize an array of the pointers of the pascal rows */
	int **pointers = (int**)malloc((n)*sizeof(int*));
	
	pascal_triangle(n, 0, pointers);
	print_array(pointers, n);
	free(pointers);
}
