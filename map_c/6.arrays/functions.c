#include <stdio.h>
#include <limits.h>
#include "question_6.h"

/* Find the maximum product of two integers in an array */
void find_maximum_product_of_two_integers(int arr[], int len)
{
    /* Initialize 4 pointers for the 2 largest and 2 smallest numbers */
    int max_a, max_b, min_a, min_b;

    max_a = max_b = INT_MIN;
    min_a = min_b = INT_MAX;

    /* Find the max_a, max_b, min_a, min_b */
    for(int i = 0; i < len; ++i)
    {
        if (arr[i] > max_a)
        {
            max_b = max_a;
            max_a = arr[i];
        }
        else if (arr[i] > max_b)
            max_b = arr[i];
        
        if (arr[i] < min_a)
        {
            min_b = min_a;
            min_a = arr[i];
        }
        else if (arr[i] < min_b)
            min_b = arr[i];
    }

    /* Calculate and print the maximum product of two integers */
    if (max_a * max_b > min_a * min_b)
        printf("%d, %d\n",max_a, max_b);
    else
        printf("%d, %d\n",min_a, min_b);
}

/* Find the element that divides the array into two arrays that their sum is equal (or -1 if it does not exist).*/
int find_the_array_divider(int arr[], int len)
{
    /* Initialize sum and pointers and boolean vatibale for 2 sub arrays */
    int sum_start = 0, sum_end = 0, start_ptr = 0, end_ptr = len-1, start_move = 1, end_move = 1;

    /* Calculate sum of the sub_arrays and moving the pointer forward if the sum of the his sub_array smaller then the second */
    while(end_ptr - start_ptr != 1)
    {
        if(start_move)
            sum_start += arr[start_ptr];
        if(end_move)
            sum_end += arr[end_ptr];

        if (sum_start > sum_end)
        {
            --end_ptr;
            start_move = 0;
            end_move = 1;
        }
        else
        {
            ++start_ptr;
            start_move = 1;
            end_move = 0;
        }
    }

    /* print the index if two sub_arrays is equal */
    if (sum_start == sum_end)
        return start_ptr;
    else
        return -1;
}