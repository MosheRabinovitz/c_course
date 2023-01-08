#include <stdio.h>
#include <stdlib.h>
#include "distance_from_string.h"

#define ASCII 256


void arrange(char * arr[], int n, char * s)
{
	int * str_arr = fill_ascii(s);
	
	int index = 0;
	for (int j = 0; j < ASCII ;++j)
		for (int i = index; i < n ;++i)
		{
			int distance = distanse(str_arr, arr[i]);
			if (distance == j)
			
				swap(&(arr[i]), &(arr[index++]));
			
			if(index == n)
			{
				free(str_arr);
				return;
			}
		}
	
	free(str_arr);
}




int * fill_ascii(char * s)
{
	int * arr = (int *) calloc (ASCII, sizeof(int));
	int i = 0;
	while (*(s+i) != '\0')
	{
		*(arr + *(s+i)) = 1;
		++i;
	}
	return arr;
}


int distanse(int * arr1, char * k)
{
	int dist = 0;
	int * arr2 = fill_ascii(k);
	
	for (int i = 0; i < ASCII; ++i)
	{
		if(*(arr1+i) == 1 && *(arr2+i) == 0)
			++dist;
	}
	free(arr2);
	return dist;
}


void swap(char ** a, char ** b)
{
	char * temp = *a;
	*a = *b;
	*b = temp;
}


void print(char * arr[], int n)
{
	for (int i = 0; i < n ;++i)
	{
		printf("%s, ", arr[i]);
	}
	printf("\n");
}
