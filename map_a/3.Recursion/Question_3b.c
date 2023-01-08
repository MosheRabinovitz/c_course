#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 30

int MAX = 1000000;
int array[SIZE];// = {90,70,50, 0,30,10,80,60,20,40};
time_t t1;

int partition(int pivot, int start, int end, int* dup);
void printArray();
void swap(int *a, int *b);
void init();
int main();

// The function that sorts
void quick_sotr(int start, int end)
{
	// Check the stopping condition
	int size = (end - start)+1;
	if (size <=1)
		return;
	
	// initialize number for pivot and for count the appearances of the value of array[pivot]
	int dup = 0;
	int pivot = start + (random()%size);
	
	// Call to partition function and get the pivot_index in the sorted subarray
	int index = partition(pivot, start, end, &dup);
	
	// Run the algorithm recursively of two sides of the pivot
	quick_sotr(start, index -1);
	quick_sotr(index + dup +1 , end);
}

// partition around the pivot and arrange the smaller than the pivot to his left and the larger to his right
int partition(int pivot, int start, int end, int* dup)
{
	// Swap the array[pivot] with the first index
	swap(&array[pivot], &array[start]);
	int pivot_index = start;
	
	// Do the partition
	for(int i = (start +1); i <= end; ++i)
	{
		// If the value is smaller then the pivot change places and increse the pivot_index with 1
		if (array[i] < array[pivot_index])
		{
			swap(&array[i], &array[pivot_index]);
			++pivot_index;
			swap(&array[i], &array[pivot_index + *dup]);
		}
		
		// If the value is equal to pivot change places with the value after all the same pivot values and increse the dup with 1
		else if (array[i] == array[pivot_index])
		{
			++*dup;
			swap(&array[i], &array[pivot_index+ *dup]);
		}
	}
	
	return (pivot_index); 
}

// Swap 2 values in the original places
void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp ;
}


// Initialize array with ranndom values
void init()
{
	int i;
	srand ((unsigned) time (&t1));
	for(i=0; i<SIZE; ++i)
		array[i] = rand()%SIZE+1;
}

void printArray()
{
	int i;
	for(i=0; i<SIZE; ++i)
		printf("%d, ",array[i]);
	printf("\n");
}


int main()
{
	init();
	printf("The original array: \n");
	printArray();
	printf("\nThe array after sorted:");
	quick_sotr(0, SIZE-1);
	printf("\n");
	printArray();
	
}
