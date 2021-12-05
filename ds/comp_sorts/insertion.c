#include <assert.h>
#include "comparison.h"

void insertion(int *arr, size_t size)
{
    size_t i, curr, prev;
    int temp;

    assert(arr);

    for (i = 1 ; i < size ; ++i)
    {
        curr = i;
        prev = i - 1;
        temp = arr[curr];

        for(;temp < arr[prev] && curr > 0; --curr , --prev)
        {
            arr[curr] = arr[prev];
        }
        arr[curr] = temp;
    }
    
}



