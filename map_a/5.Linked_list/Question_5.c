#include <stdio.h>
#include <stdlib.h>

/* Prototypes
void insert(struct Node** head_ref, int new_data);
void printList(struct Node* head);
static void reverse(struct Node** head_ref);
int main() */

// Link list node
struct Node {
	int data;
	struct Node* next;
};

// Function to add a new node
void insert(struct Node** head_ref, int new_data)
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->data = new_data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;

}

// Function to print linked list
void printList(struct Node* head)
{
	struct Node* temp = head;
	while (temp != NULL)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
}

// Function to reverse the linked list
static void reverse(struct Node** head_ref)
{	
	struct Node* new_list = NULL;
	for(struct Node* temp = *head_ref; temp != NULL; temp = temp->next)
		insert(&new_list, temp->data);
	*head_ref = new_list;
}


int main()
{
	// Start with the empty list
	struct Node* head = NULL;
	insert(&head, 20);
	insert(&head, 4);
	insert(&head, 15);
	insert(&head, 85);
	printf("The linked list is:\n");
	printList(head);
	
	// Create pointer to the head
	struct Node** a = &head;
	reverse(a);
	printf("\n\n");
	printf("The linked list now is:\n");
	printList(head);
	printf("\n");
}
