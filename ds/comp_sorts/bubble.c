#include <assert.h>
#include "comparison.h"

void swap(int *x, int *y)
{
    int temp = 0;
    temp = *x;
    *x = *y;
    *y = temp;
}

void bubble(int *arr, size_t size)
{
    size_t i = 0;
    size_t j = 0;
    assert(arr);

    for(i = 0; i < size-1 ; ++i)
    {
        for(j = 0; j < size - i - 1; ++j)
        {
            if (arr[j] > arr[j+1])
            {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}






