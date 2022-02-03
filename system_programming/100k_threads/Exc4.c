#include <pthread.h>		/* for threads 		*/
#include <stdlib.h>			
#include <unistd.h>			/* for sleep		*/
#include <stdio.h>			
#include "th_100k.h"	

#define ARR_SIZE 32000
#define NUM_OH_THREADS ARR_SIZE

static int arr[ARR_SIZE] = {0};

static void *FillArr(void *arg)
{
	arr[(size_t) arg] = (size_t) arg;

	return NULL;
}

void Exc4(void)
{
	size_t i = 0;
	static pthread_t tid[NUM_OH_THREADS] = {0};

	for (i = 0; i < NUM_OH_THREADS; i++)
	{
		if (pthread_create(tid + i, NULL, FillArr, (void *) i))
		{
			printf("thread create has an error");
		}
	}
	
	for (i = 0; i < NUM_OH_THREADS; i++)
	{
		if (pthread_join(tid[i], NULL))
		{
			printf("thread join has an error");
		}
	}

	for (i = 0; i < ARR_SIZE; i++)
	{
		printf("%d\n", arr[i]);
	}

}

