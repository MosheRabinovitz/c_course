#include <stdio.h>

void change_value(int *a, int *b);
void swap(int **a, int **b);
void print_array(int * array, int size);


/* B task*/
void change_value(int *a, int *b)
{
	int tmp = *a;
	*a = *a + *b;
	*b = tmp - *b;
	if (*b < 0)
		*b = -*b;
}

/* Swap two pointers - A task */
void swap(int **a, int **b)
{
	int *tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/* Print array */
void print_array(int * array, int size)
{
	int arr_size = size;
	for(int i = 0; i < arr_size; ++i)
		printf("%d,", *(array+i));
	printf("\n");
}


int main(){
	printf("A.\n");
	int arr_a[ ] = {5,3,2,6};
	int arr_b[ ] = {6,9,2,5,7,3};
	int* a = arr_a;
	int* b = arr_b;
	
	print_array(a, 4);
	print_array(b, 6);
	
	swap(&a, &b);
	printf("\n");
	
	print_array(a, 6);
	print_array(b, 4);
	
	printf("\nB.\n");
	int c = 3;
	int d = 7;
	change_value(&c, &d);
	printf("%d, %d\n" ,c , d);
}
