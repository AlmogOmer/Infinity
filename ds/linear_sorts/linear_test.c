#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linear.h"

static int my_random(int min, int max);
static void fill_array(int *arr,int size);
static int sort_check(int *arr, int size);



int main()
{
    int size = 5000;
    int bits = 4; 
    int *arr1 = NULL;
    int *arr2 = NULL;

    arr1 = (int *)malloc(size*sizeof(int));
    if (NULL == arr1)
    {
        exit(1);
    }

    arr2 = (int *)malloc(size*sizeof(int));
    if (NULL == arr2)
    {
        exit(1);
    }

    fill_array(arr1,size);
    fill_array(arr2,size);
    
    counting_sort(arr1, size);
    
    if (0 == sort_check(arr1, size))
    {
        printf("failed at counting_sort\n");
    }

    radix_sort(arr2, size, bits);
     
    if (0 == sort_check(arr2, size))
    {
        printf("failed at radix_sort\n");
    }

    free(arr1);
    free(arr2);
    return 0;
}

static int my_random(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

static void fill_array(int *arr,int size)
{
  int i = 0;
  srand(time(0));

  for (i = 0; i < size; ++i)
	{
        arr[i] = my_random(0,100);
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




