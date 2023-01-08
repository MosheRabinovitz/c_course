#include <stdio.h>

#define ARRAY_SIZE 10

void reverse(int Array[ARRAY_SIZE]);
void insertionSort(int  arr[ARRAY_SIZE]);


int main()
{
	int i, Array[ARRAY_SIZE];
	printf(" Enter elements into the Array :n ");
	for (i=0; i< ARRAY_SIZE ; i++)
	{
		printf("Enter %2d elements : ",i);
		scanf("%d",&Array[i]);
	}

	insertionSort(Array);
	reverse(Array);
	
	printf("\n");
	printf("here is the new Array :");
	for (i=0; i< ARRAY_SIZE ; i++)
	{
		printf("%3d",Array[i]);
	}
	printf("\n");
	return 0;
}

/* Reverse the values in array*/
void reverse(int Array[ARRAY_SIZE])
{
	int temp,i;
	for ( i=0; i < (ARRAY_SIZE/2) ; i++)
	{
		temp = Array[ARRAY_SIZE-1-i];
		Array[ARRAY_SIZE-1-i] = Array[i];
		Array[i] =temp;
	}
}


/* Insertion Sort */
void insertionSort(int  arr[])
{
	int i, j, num;
	
	
	for (i = 1; i < ARRAY_SIZE; ++i)
	{
		if (arr[i] < arr[i - 1])
		{
			num = arr[i];
			j = i - 1;
			while (j >= 0 && num < arr[j])
			{
				arr[j + 1] = arr[j];
				j--;
			}
			arr[j + 1] = num;
		}
	}
}
