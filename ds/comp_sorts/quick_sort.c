#include <assert.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "comparison.h"

static void QuickSortRec(void *base, size_t left, size_t right, size_t size, cmp_func_t cmp_func);
static size_t Partition(void *base, size_t left, size_t right, size_t size, cmp_func_t cmp_func);
static void Swap(void *x, void *y, size_t size);

void quick_sort(void *arr, size_t arr_size, size_t elem_size, cmp_func_t cmp_func)
{
    QuickSortRec(arr, 0, arr_size, elem_size, cmp_func);

}

static void QuickSortRec(void *base, size_t left, size_t right, size_t size, cmp_func_t cmp_func)
{
	size_t pivot = 0;
	if (left < right)
	{	
		pivot = Partition(base, left, right, size, cmp_func);
		QuickSortRec(base, left, pivot, size, cmp_func);
		QuickSortRec(base, pivot+1, right, size, cmp_func);
	}

}

static size_t Partition(void *base, size_t left, size_t right, size_t size, cmp_func_t cmp_func)
{
	void *left_runner, *runner, *right_runner, *pivot;
	
	if(0 != right)
	{
		--right; 
	}
	
	left_runner = (char *) base + left * size;
	runner = left_runner;
	right_runner = (char *) base + right * size;
	pivot = right_runner;

	while (runner < right_runner)
	{
		if (cmp_func(runner, pivot) <= 0) /* runner is smaller than pivot*/
		{
			Swap(runner, left_runner, size);
			left_runner = (char *) left_runner + size;
		}

		runner = (char *) runner + size;
	}

	if (cmp_func(left_runner, pivot) <= 0)
	{
		return (((char *) pivot - (char *) base) / size);
	}
	
	Swap(pivot, left_runner, size);

	return (((char *) left_runner - (char *) base) / size);
}

static void Swap(void *x, void *y, size_t size)
{
	void *tmp = malloc(size);
	memcpy(tmp, x, size);
	memcpy(x, y, size);
	memcpy(y, tmp, size);

	free(tmp);
}










