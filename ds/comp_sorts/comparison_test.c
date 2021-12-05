#include <stdio.h>
#include <time.h>
#include "comparison.h"

typedef void (*sort_func) (int *, size_t);

static int sort_check(int *arr, int size); 
static void fill_array(int *arr,int *qsort_arr ,int size);
static void test(sort_func func, char *str);
static int compare_int(const void *x, const void *y);

int main()
{
    
    test(bubble, "bubble");
    test(insertion, "insertion");
    test(selection, "selection");
    
    return 0;
}


static void fill_array(int *arr,int *qsort_arr ,int size)
{
  int i = 0;
  srand(time(0));

  for (i = 0; i < size; ++i)
	{
        arr[i] = rand();
        qsort_arr[i] = arr[i];
    }

}


static int sort_check(int *arr, int size)
{
    int i =0;
    for (i = 0; i < size-1; ++i)
	{
		if (arr[i] > arr[i+1])
        {
            return 0;
        }
    }

    return 1;

}

static void test(sort_func func, char *str)
{
    int size = 5000;
    int arr[5000];
    int qsort_arr[5000];
    clock_t start, end;

    fill_array(arr,qsort_arr,size);
    
    start = clock();
    func(arr, size);
    end = clock();
    printf("Time for %s is %f\n", str, (double)(end-start)/CLOCKS_PER_SEC);

    start = clock();
    qsort(qsort_arr, 5000, sizeof(int), compare_int);
    end = clock();
    printf("Time for qsort is %f\n", (double)(end-start)/CLOCKS_PER_SEC);

    if (sort_check(arr, size) == 0)
    {
        printf("failed in %s\n", str);
    }
}



static int compare_int(const void *x, const void *y)
{
	return (*(int*)x - *(int*)y);
}



