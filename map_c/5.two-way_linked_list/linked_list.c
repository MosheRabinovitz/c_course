#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


/* Print the list from the head */
void print_list(CellPtr list)
{
	CellPtr p = list;
	while(p)
	{
		printf("%d, ", p->contents);
		p = p->next;
	}
	printf("\n");		
}


/* Print the list from the tail */
void print_rev(CellPtr list)
{
	CellPtr p = list;
	while (p)
	{
		printf("%d, ", p->contents);
		p = p->prev;
	}
	printf("\n");	
}


/* Insert the input to the beginning of the list */
CellPtr insert_first (CellPtr list, int input)
{
	CellPtr new_cell = (CellPtr)malloc(sizeof(Cell));
	new_cell->contents = input;
	new_cell->prev = NULL;
	new_cell->next = list;
	if(list)
		list->prev = new_cell;
	return new_cell;
}


/* Remove the first node list and save his data in the output */
CellPtr remove_first (CellPtr list, int *output)
{
	*output = list->contents;
	CellPtr new_first = list->next;
	free(list);
	new_first->prev = NULL;
	return new_first;	
}


/* Insert the input to the end of the list */
CellPtr insert_last (CellPtr list, int input)
{
	CellPtr new_cell = (CellPtr)malloc(sizeof(Cell));
	new_cell->contents = input;
	new_cell->next = NULL;
	new_cell->prev = list;
	if(list)
		list->next = new_cell;
	return new_cell;
}


/* Remove the last node list and save his data in the output */
CellPtr remove_last (CellPtr list, int *output)
{
	CellPtr new_last = list->prev;
	*output = list->contents;
	free(list);
	new_last->next = NULL;
	return new_last;	
}

/* Clean the memory */
void clean_list(CellPtr list)
{
	if (!list)
		return;
		
	if (!list->prev)
	{
		CellPtr p = list, q;
		while(p)
		{
			q = p->next;
			free(p);
			p = q;
		}
	}
	else
	{
		CellPtr p = list, q;
		while(p)
		{
			q = p->prev;
			free(p);
			p = q;
		}
	}
}
