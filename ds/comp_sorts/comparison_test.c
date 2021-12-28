#include <stdio.h>
#include <time.h>
#include "comparison.h"
#include<assert.h>

typedef void (*sort_func) (int *, size_t);

static int sort_check(int *arr, size_t size); 
static void fill_array(int *arr,int *qsort_arr ,size_t size);
static void test(sort_func func, char *str);
static int compare_int(const void *x, const void *y);
static void marge_test(void);
static void SearchTest(void);

int main()
{
    
    test(bubble, "bubble");
    test(insertion, "insertion");
    test(selection, "selection");
    
    marge_test();
    SearchTest();
    
    return 0;
}


static void fill_array(int *arr,int *qsort_arr ,size_t size)
{
  size_t i = 0;
  srand(time(0));

  for (i = 0; i < size; ++i)
	{
        arr[i] = rand();
        qsort_arr[i] = arr[i];
    }

}


static int sort_check(int *arr, size_t size)
{
    size_t i =0;
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
    size_t size = 5000;
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


static void SearchTest(void)
{
	int find_arr[5000] = {0};
	size_t i = 0;

	for (i = 0; i < 5000; i++)
	{
		find_arr[i] = i + 1;
	}
	
	for (i = 0; i < 5000; i++)
	{
        assert(&find_arr[i] == RecBinarySearch(find_arr, 5000, sizeof(find_arr[0]), compare_int ,&find_arr[i]));
        assert(&find_arr[i] == IterBinarySearch(find_arr, 5000, sizeof(find_arr[0]), compare_int ,&find_arr[i]));
    }

	puts("SUCCESS");
}


static void marge_test(void)
{
    size_t nmemb = 5000;
    int arr[5000];
    int qsort_arr[5000];
    clock_t start, end;
    size_t i = 0;

    fill_array(arr,qsort_arr,nmemb);

    start = clock();
    MergeSort(arr, nmemb, sizeof(arr[0]), compare_int);
    end = clock();
    printf("Time for merge sort is: %f\n", (double)(end-start)/CLOCKS_PER_SEC);
    
    
    /*printf("*****after sorting*****\n");
    for (i = 0; i < nmemb; ++i)
	{
        printf("%d\n", arr[i]);
    }*/
    
    
    
    start = clock();
    qsort(qsort_arr, nmemb, sizeof(arr[0]), compare_int);
    end = clock();
    printf("Time for qsort is %f\n", (double)(end-start)/CLOCKS_PER_SEC);

    if (sort_check(arr, nmemb) == 0)
    {
        printf("fail in merge sort\n");
    }
	

}




