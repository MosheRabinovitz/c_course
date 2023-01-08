#include <stdio.h>

void find_primes(int * arr, int n, int num, int * p1, int * p2);
int binary_search(int * arr, int num, int start, int end);

void find_primes(int * arr, int n, int num, int * p1, int * p2)
{
	
	int k;
	for (int i = 0; i < n; ++i)
	{
		
		k = num - *(arr +i);
		if (binary_search(arr, k, 0, n))
		{
			*p1 = *(arr +i);
			*p2 = k;
			return;
		}
	}
}


int binary_search(int * arr, int num, int start, int end)
{
	int size = end - start;
	if (size == 0)
	{
		if (*(arr+start) == num)
			return 1;
		return 0;
	}
	if (size == 1)
	{
		if (*(arr+start) == num || *(arr+end) == num)
			return 1;
		else
			return 0;
	}
	if (*(arr+start+(size/2)) == num)
		return 1;
	
	if (*(arr+start+(size/2)) > num)
		return binary_search(arr, num, start, start+size/2);
	
	return binary_search(arr, num, start+size/2, end);
}
