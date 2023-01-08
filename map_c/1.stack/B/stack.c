#include "stack.h"
#include <stdio.h>
#include <stdlib.h>


/* Push the num into the stack */
void push(Stack ** stack, int num)
{
    if (isFull(*stack))
    {
        printf("The stack is full\n");
        return;
    }

    Stack * new_node = (Stack *) malloc(sizeof(Stack));
    new_node->value = num;
    new_node->next = *stack;
    *stack = new_node;

}

/* Pop the last elements from the stack */
int pop(Stack ** stack)
{
    if (isEmpty(*stack))
    {
        printf("The stack is empty\n");
        return;
    }
    int result = (*stack)->value;
    Stack * next = (*stack)->next;
    free(*stack);
    *stack = next;

    return result;
}

/* Check if the stack is empty */
int isEmpty(Stack * stack)
{
    if(stack)
        return 0;
    
    return 1;
}

/* Check if the stack is full */
int isFull(Stack * stack)
{
    int size = 0;
    Stack * p = stack;
    while (p != NULL)
    {
        p = p->next;
        ++size;
    }
    
    if(size == STK_SIZE)
        return 1;
    
    return 0;
}

/* Clean and free the tree */
void clean(Stack ** stack)
{
    Stack * p = *stack, * q;;
    while (p != NULL)
    {
        q = p;
        p = p->next;
        free(q);
    }
    *stack = NULL;
}