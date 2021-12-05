#include <assert.h>
#include "comparison.h"


void selection(int *arr, size_t size)
{
    size_t i = 0;
    size_t j = 0;
    size_t min = 0;
    assert(arr && size > 0);

    for(i = 0; i < size - 1 ; ++i)
    {
        min = i;
        
        for(j = i + 1;j < size; ++j)
        {
           if(arr[j] < arr[min])
           {
               min  = j;
           }
        }

        swap(&arr[min], &arr[i]);
    }
}


