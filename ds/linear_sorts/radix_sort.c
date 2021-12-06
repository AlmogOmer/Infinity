#include <stdlib.h>
#include<stdio.h>
#include "linear.h"

void counting_for_radix(int *arr, int size, int mask, int counter);
static void PrintArr(int *arr, size_t size)
{
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
        }
        printf("\n");
}
void radix_sort(int *arr, int size , int bits)
{
    
   int mask, max, counter;
   counter = 0;
   max = max_arr(arr, size);
   mask = (1<<bits)-1;
  
   while(max)
   {
       counting_for_radix(arr, size, mask, counter);
       counter += bits;
       max = max >> bits;
   }

}

void counting_for_radix(int *arr, int size, int mask , int counter)
{
    int i;
    int *result_arr = NULL;
    int *idx_arr = NULL;

    
    idx_arr = (int*)calloc(mask + 1, sizeof(int));
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
        ++idx_arr[arr[i]>>counter & mask];
    } 
    
    for(i = 1; i < mask+1 ; ++i)
    {
        idx_arr[i] = idx_arr[i-1] + idx_arr[i];
    }
    
    for (i = 0; i<size ; ++i)
    {
        
        result_arr[idx_arr[(arr[size-i-1]>>counter) & mask]-1] = arr[size-i-1];
        --idx_arr[arr[size-i-1]>>counter & mask];

    } 

    for (i = 0; i<size ; ++i)
    {
        arr[i] = result_arr[i];
    } 

    free(idx_arr);
    free(result_arr);
}
