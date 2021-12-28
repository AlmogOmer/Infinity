#include <assert.h>
#include "comparison.h"


static void QuickSortRec(void *base, void *tmp, size_t left, size_t right, size_t size, cmp_func_t cmp_func)
{
	size_t pivot = 0;

	if (right - left < 2)
	{
		return;
	}

	/*pivot = Partition(base, tmp, left, right, size, cmp_func);*/
	QuickSortRec(base, tmp, left, pivot, size, cmp_func);
	QuickSortRec(base, tmp, pivot + 1, right, size, cmp_func);
}

void quick_sort(void *arr, size_t arr_size, size_t elem_size, cmp_func_t cmp_func)
{
	if (arr_size > 1)
	{
		void *tmp = malloc(elem_size);
        if(!tmp)
        {
            exit(1);
        }
		
        QuickSortRec(arr, tmp, 0, arr_size, elem_size, cmp_func);
		free(tmp);
	}
}





