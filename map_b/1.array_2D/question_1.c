#include <stdio.h>
#include <stdlib.h>

#define n 2
#define m 5


void fill_the_list(int* arr)
{
	for (int i = 0; i < m*n; i+=m)
	{
		printf("Enter number in list %d: \n", (i/m)+1);
		for (int j = 0; j < m; ++j)
		{
			int k;
			printf("Enter the element %d: ", j+1);
			scanf("%d", &k);
			*(arr+i+j) = k;
		}
	}
}


void find_big_value(int* arr)
{
	for (int i = 0; i < n*m; i+=m)
	{
		int big_value = 0;
		for (int j = 0; j < m; ++j)
		{
			if (*(arr+i+j) > big_value)
				big_value = *(arr+i+j);
		}
		printf("the big number in list %d is: %d\n", (i/m)+1, big_value);
	}
}


void sum_odd_numbers(int* arr)
{
	int sum_odd = 0;
	for (int i = 0; i < n*m; i+=m)
		for(int j = 0; j < m; ++j)
			if (*(arr+i +j)%2==1)
				sum_odd += *(arr+i+j);
	printf("the sum_odd_numbers is: %d\n", sum_odd);
}


void is_prime(float num)
{
	if (num <= 1 || num != (int)num)
	{
		printf("Pleas enter a valid number\n");
		exit(1);
	}

	for (int i = 2; i < num/2; ++i)
		if((int)num/i == num/i)	
		{
			printf("The number %f isn't a prime number\n", num);
			return;
		}
	printf("The number %f is a prime number\n", num);
}


int main()
{	

	printf("Question A.\n");
	int num[n][m];
	fill_the_list(*num);
	find_big_value(*num);
	sum_odd_numbers(*num);
	
	printf("\nQuestion B.\n");
	float number;
	printf("Enter a number to check if is a prime number: ");
	scanf("%f", &number);
	is_prime(number);
}