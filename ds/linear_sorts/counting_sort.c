#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void counting_sort(int *arr, int size, int range); 

int main()
{
    int size = 5000;
    int range = 100 + 2;
    int *arr = NULL;
    
    arr = (int *)malloc(size*sizeof(int));
    if (NULL == arr)
    {
        exit(1);
    }

    fill_array(arr,size);
    
    counting_sort(arr, size, range);
    
    if (0 == sort_check(arr, size))
    {
        printf("failed at counting_sort\n");
    }
    

    free(arr);
    return 0;
}

void counting_sort(int *arr, int size, int range)
{
    int i;
    int *result_arr = NULL;
    int *idx_arr = NULL;
    
    idx_arr = (int*)calloc(range, sizeof(int));
    if (NULL == idx_arr)
    {
        exit(1);
    }

    result_arr = (int*)malloc(size*sizeof(int));
    if (NULL == result_arr)
    {
        exit(1);
    }

    for (i = 0; i<size ; ++i)
    {
        ++idx_arr[arr[i]];
    } 

    for(i = 0; i < range-1 ; ++i)
    {
        idx_arr[i+1] = idx_arr[i] + idx_arr[i+1];
    }
    

    for (i = 0; i<size ; ++i)
    {
        result_arr[idx_arr[arr[i]]-1] = arr[i];
        --idx_arr[arr[i]];
    } 

    for (i = 0; i<size ; ++i)
    {
        arr[i] = result_arr[i];
    } 

    free(idx_arr);
    free(result_arr);
}



