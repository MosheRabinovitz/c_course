/* Link list node */
struct Node {
	int name;
	struct Node* next;
};


/* Prototypes */
void insert_to_list(struct Node** head_ref, int name);
void remove_from_list(struct Node** head_ref, int name);
void printList(struct Node* head);