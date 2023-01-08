#include <stdio.h>
#include <stdlib.h>

int** create_lists_of_list(int number_of_arrays, int *len_of_arr)
{
	int **arr;
	arr = (int**)malloc(sizeof(int*)*number_of_arrays);
	for (int i = 0; i < number_of_arrays; ++i)
	{
		printf("Enter number of elements in list %d: ", i + 1);
		int m;
		scanf("%d", &m);
		*(len_of_arr + i) = m;
		*(arr + i) =  malloc(sizeof(int) * m);
		int k;
		for (int j = 0; j < m; ++j)
		{
			printf("Enter the element %d: ", j+1);
			scanf("%d", &k);
			*(*(arr + i) + j) = k;
		}
	}
	return arr;
}


void print_arrays(int** arr, int *len_of_arr, int n)
{
	for (int j = 0; j < n; ++j)
	{
		printf("the list number %d is: ", j);
		for (int i = 0; i < *(len_of_arr + j); i++)
		{
			printf("%d ", *(*(arr + j) + i));
		}
		printf("\n");
	}
}


void clean_memory(int** arr, int n)
{
	for (int i = 0; i < n; i++)
		free(*(arr + i));	
	free(arr);
}


int main()
{
	printf("Enter number of lists: ");
	int n;
	scanf("%d", &n);
	int* len_of_arr = malloc(sizeof(int) * n);
	int** a = create_lists_of_list(n, len_of_arr);
	print_arrays(a, len_of_arr, n);
	clean_memory(a, n);
}
