#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calculator.h"


/* insert the value (cast of the char) into the stack */
void insert(char * arg)
{
    stack[stk_ptr++] = atoi(arg);
}

/* Calculate the operator that given on the 2 last stack elements and push the result into the stack */
void calculate(char operator)
 {
    int num1, num2, result;
    num1 = stack[stk_ptr-1];
    --stk_ptr;
    num2 = stack[stk_ptr-1];
    --stk_ptr;
    
    switch (operator)
    {
    case ('+'):
        result = num1 + num2;
        break;
    case ('-'):
        result = num1 - num2;
        break;
    case ('x'):
        result = num1 * num2;
        break;
    case ('/'):
        result = num1 / num2;
        break;
    
    default:
        return;
    }

    stack[stk_ptr++] = result;
 }

/* Print the result calculating */
 void print_result()
 {
    printf("The result is: %d\n", stack[stk_ptr-1]);
 }