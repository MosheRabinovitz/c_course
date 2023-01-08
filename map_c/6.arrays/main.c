#include <stdio.h>
#include "question_6.h"


int main()
{
    /* Initialize array to chack */
    int arr1[] = {-10,-3,5,6,-2};
    int arr2[] = {2, 3, 4, 1, 4, 5};
    int arr3[] = {10, -3, -20};
    int arr4[] = {1, 4, 2, 5};

    /* Run the 1st function on the arrays */
    find_maximum_product_of_two_integers(arr1, 5);
    find_maximum_product_of_two_integers(arr2 ,6);
    find_maximum_product_of_two_integers(arr3, 3);
    find_maximum_product_of_two_integers(arr4 ,4);
    
    /* Run the 2nd function on the arrays and print the results */
    int res1 = find_the_array_divider(arr1, 5);
    int res2 = find_the_array_divider(arr2, 6);
    int res3 = find_the_array_divider(arr3, 3);
    int res4 = find_the_array_divider(arr4, 4);

    printf("%d\n", res1);
    printf("%d\n", res2);
    printf("%d\n", res3);
    printf("%d\n", res4);
}