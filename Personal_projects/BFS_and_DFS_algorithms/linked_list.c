#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

/* Function to add a new node */
void insert_to_list(struct Node** head_ref, int name)
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->name = name;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}


/* Function to remove name */
void remove_from_list(struct Node** head_ref, int name)
{	
	struct Node* temp = *head_ref;
	if (temp->name == name)
	{
		*head_ref = temp->next;
		free(temp);
	}
	else
	{
		while (temp->next->name != name)
			temp = temp->next;
	
		struct Node* to_remove = temp->next;
		temp->next = temp->next->next;
		free(to_remove);
	}
	
}


/* Function to print linked list */
void printList(struct Node* head)
{
	struct Node* temp = head;
	while (temp != NULL)
	{
		printf("%d ", temp->name);
		temp = temp->next;
	}
	printf("\n");
}