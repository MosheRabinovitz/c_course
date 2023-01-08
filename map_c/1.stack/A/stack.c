#include <stdio.h>
#include "stack.h"

/* Initialize tho pointer of the stack to -1 */
void init(Stack * stack)
{
    stack->stk_ptr = -1;
}

/* Push the num into the stack */
void push(Stack * stack, int num)
{
    if (isFull(stack))
    {
        printf("The stack is full\n");
        return;
    }
    stack->stack[++stack->stk_ptr] = num;
}

/* Pop the last elements from the stack */
int pop(Stack * stack)
{
     if (isEmpty(stack))
    {
        printf("The stack is empty\n");
        return;
    }
    int result = stack->stack[stack->stk_ptr--];
    return result;
}

/* Check if the stack is empty */
int isEmpty(Stack * stack)
{
    if(stack->stk_ptr == -1)
        return 1;
    
    return 0;
}

/* Check if the stack is full */
int isFull(Stack * stack)
{
    if(stack->stk_ptr == STK_SIZE-1)
        return 1;
    
    return 0;
}