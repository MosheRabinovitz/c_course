#include "sub_arrays.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    
    char arr1[] = {N,'A','B','C','D','E','F','G','H','I','J'};

    // Initiazlize array with size of N (N determined by define)
    char * arr = (char*) malloc(N*sizeof(char));
    if (arr == NULL)
            exit(5);
    for(int i = 0; i < N+1; ++i)
        *(arr + i) = arr1[i];
    
    // Create list of pointers to avoid unnecessary recursion
    char ** head = create_list_of_pointers();

    // Find all the sub arrays
    sub_arrays(arr, head);

    print_and_clean(head);
}
