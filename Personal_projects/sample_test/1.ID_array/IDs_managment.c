#include <stdlib.h>
#include "IDs_managment.h"


int * create_arr(int len)
{
	int * arr = (int *)calloc(sizeof(int), len);
	return arr;	
}

int * insert_id(int * arr, int pn, int id)
{
	int i = 0;
	while (i<pn && *(arr+i) != 0)
	{
		++i;
	}
	if (i < pn)
	{
		*(arr+i) = id;
		return arr;
	}
	
	int * new_arr = create_arr(pn+1);
	for(int i = 0; i<pn; ++i)
		*(new_arr + i) = *(arr + i);
	free(arr);
	*(new_arr + pn) = id;
	
	return new_arr;
}
