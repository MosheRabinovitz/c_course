#include <stdio.h>

void towers_of_hanoi(int n, char from_rod, char to_rod, char aux_rod)
{
	if (n==0)
		return;
		
	towers_of_hanoi(n-1, from_rod, aux_rod, to_rod);
	printf("Move disk %d from %c to %c\n", n, from_rod, to_rod);
	towers_of_hanoi(n-1, aux_rod, to_rod, from_rod);
		
}


int main()
{	
	int n;
	printf("Enter the number of disks: ");
	
	scanf("%d", &n);
	
	towers_of_hanoi(n, 'A', 'B', 'C');
	
}
