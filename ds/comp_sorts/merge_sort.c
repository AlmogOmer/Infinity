#include <assert.h>
#include<stdlib.h>
#include<string.h>
#include "comparison.h"
static void MergeSortRec(void *src, void *dest, size_t start, size_t end, size_t size, cmp_func_t cmp_func);
static void Merge(void *src, void *dest, size_t start, size_t mid, size_t end, size_t size, cmp_func_t cmp_func);

void MergeSort(void *base, size_t nmemb, size_t size, cmp_func_t cmp_func)
{
	void *aux_arr = malloc(nmemb * size);
    if(!aux_arr)
    {
        exit(1);
    }

	memcpy(aux_arr, base, nmemb * size);

	MergeSortRec(aux_arr, base, 0, nmemb-1, size, cmp_func);

	free(aux_arr);
}


static void MergeSortRec(void *src, void *dest, size_t start, size_t end, size_t size, cmp_func_t cmp_func)
{
	if (end > start)
	{
		size_t mid = (start + end)/ 2;

		MergeSortRec(src,dest, start, mid, size, cmp_func);
		MergeSortRec(src,dest, mid+1, end, size, cmp_func);

		Merge(src, dest, start, mid, end, size, cmp_func);
	}
}

static void Merge(void *src, void *dest, size_t start, size_t mid, size_t end, size_t size, cmp_func_t cmp_func)
{
	size_t i = start;	/* index in left subarray */
	size_t j = mid+1;		/* index in right subarray */
	size_t k = start;	/* index in dest */
	
	memcpy(src, dest, (end+1)*size);
	for (k = start; i <= mid && j <= end; ++k)
	{
		if (cmp_func((char *) src + i*size, (char *) src + j*size) < 0) /* src[i] is smaller*/
		{
			memcpy((char *) dest + k*size, (char *) src + i*size, size);
			++i;
		}
		else
		{
			memcpy((char *) dest + k*size, (char *) src + j*size, size);
			++j;
		}
	}

	
	while (i <= mid)
	{
		memcpy((char *) dest + k*size, (char *) src + i*size, size);
		++i;
		++k;
	}
	
	while (j<= end)
	{
		memcpy((char *) dest + k*size, (char *) src + j*size, size);
		++j;
		++k;
	}
		
	
}



