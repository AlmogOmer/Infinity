#include <stdlib.h>
#include <stdio.h>
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

int min_arr(int *arr, int size)
{
    int i = 0;
    int min = arr[0]; 

    for (i = 1; i < size; ++i)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }

    return min;
}

void counting_sort(int *arr, int size)
{
    int i;
    int max,min,idx_range;
    int *result_arr = NULL;
    int *idx_arr = NULL;
    max = max_arr(arr, size);
    min = min_arr(arr, size);
    idx_range = max-min+1;
  

    idx_arr = (int*)calloc(idx_range, sizeof(int));
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
        ++idx_arr[arr[i]- min];
    } 

    
   
    for(i = 1; i < idx_range ; ++i)
    {
        idx_arr[i] = idx_arr[i-1] + idx_arr[i];
    }

   
    for (i = 0; i<size ; ++i)
    {
        
        result_arr[idx_arr[arr[i]-min]-1] = arr[i];
        --idx_arr[arr[i]-min];
    } 

    for (i = 0; i<size ; ++i)
    {
        arr[i] = result_arr[i];
    } 

    free(idx_arr);
    free(result_arr);
}



