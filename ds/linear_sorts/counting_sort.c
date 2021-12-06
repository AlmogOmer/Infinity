#include <stdlib.h>
#include "linear.h"

int max_arr(int *arr, int size)
{
    int i = 0;
    int max = 0; 

    for (i = 0; i < size; ++i)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }

    return max;
}

void counting_sort(int *arr, int size)
{
    int i;
    int max;
    int *result_arr = NULL;
    int *idx_arr = NULL;
    max = max_arr(arr, size) + 2;
    
    idx_arr = (int*)calloc(max, sizeof(int));
    if (NULL == idx_arr)
    {
        exit(1);
    }

    result_arr = (int*)malloc(size*sizeof(int));
    if (NULL == result_arr)
    {
        exit(1);
    }

    for (i = 0; i<size ; ++i)
    {
        ++idx_arr[arr[i]];
    } 

    for(i = 0; i < max-1 ; ++i)
    {
        idx_arr[i+1] = idx_arr[i] + idx_arr[i+1];
    }
    

    for (i = 0; i<size ; ++i)
    {
        result_arr[idx_arr[arr[i]]-1] = arr[i];
        --idx_arr[arr[i]];
    } 

    for (i = 0; i<size ; ++i)
    {
        arr[i] = result_arr[i];
    } 

    free(idx_arr);
    free(result_arr);
}



