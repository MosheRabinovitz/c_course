#include <stdio.h>
#include "stack.h"

void main()
{
    /* Initialize two stacks */
    Stack stack1, stack2;

    /* Run the functions on the stack1 */
    init(&stack1);
    printf("Is empty: %d\n", isEmpty(&stack1));
    push(&stack1, 5);
    push(&stack1, 2);
    push(&stack1, 7);
    push(&stack1, 12);
    push(&stack1, 4);
    printf("Is empty: %d\n", isEmpty(&stack1));
    printf("Is full: %d\n", isFull(&stack1));
    printf("3rd element: %d, 2nd element: %d, 1st element: %d\n", pop(&stack1), pop(&stack1), pop(&stack1));

    /* Run the functions on the stack2 */
    init(&stack2);
    printf("Is empty: %d\n", isEmpty(&stack2));
    push(&stack2, 12);
    push(&stack2, 15);
    push(&stack2, 7);
    push(&stack2, 3);
    push(&stack2, 43);
    printf("Is empty: %d\n", isEmpty(&stack2));
    printf("Is full: %d\n", isFull(&stack2));

    for (int i = 0; i < 20; ++i)
        push(&stack2, i);

    printf("Is empty: %d\n", isEmpty(&stack2));
    printf("Is full: %d\n", isFull(&stack2));

    printf("3rd element: %d, 2nd element: %d, 1st element: %d\n", pop(&stack2), pop(&stack2), pop(&stack2));
}