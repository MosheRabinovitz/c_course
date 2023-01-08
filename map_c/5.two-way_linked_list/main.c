#include <stdio.h>
#include "linked_list.h"


int main()
{
    /* Initialize two_way_linked_list and run the functions of them */
    CellPtr head = NULL;
    CellPtr tail = NULL;

    head = insert_first(head, 50);
    tail = head;
    head = insert_first(head, 80);
    head = insert_first(head, 40);
    tail = insert_last(tail, 10);
    tail = insert_last(tail, 20);
   
    print_list(head);
    print_rev(tail);
    int value_removed;
    head = remove_first(head, &value_removed);
    printf("The value was %d\n", value_removed);
    tail = remove_last(tail, &value_removed);
    printf("The value was %d\n", value_removed);
    print_list(head);
    print_rev(tail);
    clean_list(head);
    
    return 0;
}
