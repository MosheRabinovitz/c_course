#include <stdlib.h>
#include <stdio.h>
#include "Pascal.h"


/* Calculate recursively the value for row level in pascal's triangle */
void pascal_triangle(int n, int size, int **pointers)
{
	/* Stoping condition */
	if (!(size == n))
	{
		/* Initialize new array for the new level */
		int* arr = (int*)malloc((size +1)*sizeof(int));
		int* prev_arr  = *(pointers + size-1);
		
		/* Fill each value with the sum of the two values above him */
		for (int i = 1; i < size; ++i)
			*(arr + i) = (*(prev_arr +(i-1)) + *(prev_arr+i));
			
		*(arr) = 1;
		*(arr + size) = 1;
		
		/* Push the array into array 'pointers' */
		*(pointers + size) = arr;
		
		/* Call recursively */
		pascal_triangle(n, size +1, pointers);	
	}

}

/* Print and free the memory occupied by the array */
void print_array(int **arr, int n)
{	
	for (int row = 0; row < n; ++row)
	{
		for (int i = 0; i < (n/2) - (row/2); ++i)
			printf("%8c", ' ');
		if(row%2 ==0)
			printf("%4c", ' ');
		for (int i = 0; i <= row; ++i)
			printf("%8d", *(*(arr+row)+i));
		printf("\n");
		free(*(arr+row));
	}
}
