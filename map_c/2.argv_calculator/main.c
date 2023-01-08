#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"


void main (int argc, char *argv[ ])
{
    /* Initialize a pointer */
    int i;
    /* Insert the numbers into the stack */
    for(i = 1; i < argc; ++i)
    {
        if (**(argv+i) <= '9' && **(argv+i) >= '0')
            insert(*(argv+i));
        else
            break;
    }

    /* Calculate the oprrators */
    for(i; i < argc; ++i)
        calculate(**(argv+i));

    /* Print the result */
    print_result();
}