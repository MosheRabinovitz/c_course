#include <stdio.h>
#include "goldbrach_theorem.h"

int main()
{
	int k;
	printf("Enter even number between 2-64: ");
	scanf("%d", &k);
	int arr [] = {2,3,5,7,11,13,17,19,23,29,31,33};
	int p1, p2;
	find_primes(arr, 12, k, &p1, &p2);
	printf("p1: %d, p2: %d\n", p1, p2);
	
}
