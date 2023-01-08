#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sub_arrays.h"


// The recursive function
void sub_arrays(char * array,  char ** head)
{   
    // Extract the array size
    char n = * array;
    // Stop condition
    if (n == 0)
    {
        char * arr = (char *) malloc(sizeof(char));
        if (arr == NULL)
            exit(5);
        *arr = 0;
        if (!(is_exist(arr, head)))
            insert(arr, head);
        else
            free(arr);
        return;
    }

    // Insert the array into the list of the pointers
    insert(array, head);

    // Create n-1 diffrent sub_arrays
    for (int i = 1; i < n+1; ++i)
    {
        char * sub_array = (char *) malloc(n * sizeof(char));
        if (sub_array == NULL)
            exit(5);
        
        *(sub_array) = n-1;
        int k = 0;
        for (int j = 1; j < n+1; ++j)
        {
            if  (j == i)
                ++k;
            else
                *(sub_array +(j-k)) = *(array + j);
        }

        // Call recusivly if the sub array not exist in the list of the pointers
        if (!(is_exist(sub_array, head)))
            sub_arrays(sub_array, head);
    }
}


// Insert array into the list of the pointers
void insert(char * array, char ** head)
{
    int j = 0;
    while (j < pow(2, N) && *(head + j) != 0)
        ++j;
    
    if (j < pow(2, N))
        *(head + j) = array;
}


// Return 1 if the array is exis in the list of the pointers
int is_exist(char * array, char ** head)
{
    
    int i = 0;
    while (i < pow(2, N) && *(head + i) != 0)
    {
        if (*(*(head + i)) == * array)
        {
            int compare = is_compare(array, *(head + i));
            if (compare)
                return 1;
        }
        ++i;
    }
    return 0;
}


// Return 1 if 2 arrays is equals
int is_compare(char * array1, char * array2)
{
    for (int i = 1; i < *(array1)+1; ++i)
        if (array1[i] != array2[i])
            return 0;
    return 1;
}


// Initialize list of the pointers in size of 2 in power of N 
char ** create_list_of_pointers()
{
    char ** head = (char **) calloc(pow(2,N), sizeof(char*));
    if (head == NULL)
        exit(5);
    return head;
}


// Print and free all the sub arrays
void print_and_clean(char ** head)
{
    for (int size = 0; size <= N; ++size)
    {
        for (int i = 0; i < pow(2, N); ++i)
        {
            if (**(head+i) == size)
            {
                print_array(*(head+i));
                free (*(head +i));
            }
        }
    }
    free(head);
}

// Print single array
void print_array(char *arr)
{
    if (*arr <= 0)
        printf("[]\n");
    else
    {
        for (int i = 1; i <= *arr; ++i)
            printf("%c,", *(arr + i));
        
        printf("\n");
    }
}
