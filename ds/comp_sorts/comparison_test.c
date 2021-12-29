#include <stdio.h>
#include <time.h>
#include<string.h>
#include "comparison.h"
#include<assert.h>

typedef void (*sort_func) (int *, size_t);

typedef struct{
	size_t id;
	char name[50];
}person_t;

static int sort_check(int *arr, size_t size); 
static void fill_array(int *arr,int *qsort_arr ,size_t size);
static void test(sort_func func, char *str);
static int compare_int(const void *x, const void *y);
static int compare_str(const void *x, const void *y);
static void marge_and_quick_test(void);
static void stability_check_quick(void);
int PrintElement(const void *data);
static void SearchTest(void);

int main()
{
    
    test(bubble, "bubble");
    test(insertion, "insertion");
    test(selection, "selection");
    
    marge_and_quick_test();
    stability_check_quick();
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

static int compare_str(const void *x, const void *y)
{
	person_t *newP = (person_t*)x;
	person_t *currP = (person_t*)y;

    return (strcmp(newP->name, currP->name));

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


static void marge_and_quick_test(void)
{
    size_t nmemb = 5000;
    int arr[5000];
    int qsort_arr[5000];
    int arrq[5000];
    clock_t start, end;

    fill_array(arr,qsort_arr,nmemb);
    
    start = clock();
    MergeSort(arr, nmemb, sizeof(arr[0]), compare_int);
    end = clock();
    printf("Time for merge sort is: %f\n", (double)(end-start)/CLOCKS_PER_SEC);
    
    start = clock();
    qsort(qsort_arr, nmemb, sizeof(arr[0]), compare_int);
    end = clock();
    printf("Time for qsort is %f\n", (double)(end-start)/CLOCKS_PER_SEC);

    if (sort_check(arr, nmemb) == 0)
    {
        printf("fail in merge sort\n");
    }

    fill_array(arrq,qsort_arr,nmemb);

	start = clock();
    quick_sort(arrq, nmemb, sizeof(arrq[0]), compare_int);
    end = clock();
    printf("Time for quick sort is: %f\n", (double)(end-start)/CLOCKS_PER_SEC);

    start = clock();
    qsort(qsort_arr, nmemb, sizeof(arr[0]), compare_int);
    end = clock();
    printf("Time for qsort is %f\n", (double)(end-start)/CLOCKS_PER_SEC);

    if (sort_check(arrq, nmemb) == 0)
    {
        printf("fail in quick sort\n");
    }
}

static void stability_check_quick(void)
{
    size_t size = 5;
    size_t i;
    person_t *p_arr[5];
    person_t p1 = {100, "Almog"};
    person_t p2 = {111, "Andrey"};
    person_t p3 = {103, "Andrey"};
    person_t p4 = {102, "Omer"};
    person_t p5 = {104, "HarryPoter"};

    p_arr[0] = &p1;
    p_arr[1] = &p2;
    p_arr[2] = &p3;
    p_arr[3] = &p4;
    p_arr[4] = &p5;

    
    printf("*****before sorting*****\n");
    for (i = 0; i < size; ++i)
	{
        PrintElement(p_arr[i]);
    }
    
    qsort(p_arr, size, sizeof(p_arr[0]), compare_str);
    
    printf("*****after sorting*****\n");
    for (i = 0; i < size; ++i)
	{
        PrintElement(p_arr[i]);
    }


}

int PrintElement(const void *data)
{
	person_t *currP = (person_t*)data;
	
	if(data)
	{	
		printf("%s", currP->name);
        printf(" %lu\n", currP->id);
		return 0;
	}
	
	return 1;
}




