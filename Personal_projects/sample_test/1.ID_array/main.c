#include <stdio.h>
#include "IDs_managment.h"

int main()
{
	int * arr = create_arr(2);
	arr = insert_id(arr, 2, 100);
	arr = insert_id(arr, 2, 101);
	arr = insert_id(arr, 2, 102);
	
	
	for (int i = 0; i < 3; ++i)
		printf("%d, ",*(arr+i));
	printf("\n");
}
