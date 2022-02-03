#include <pthread.h>		
#include <stdlib.h>			
#include <unistd.h>			
#include <stdio.h>
#include "th_100k.h"		

#define ARR_SIZE 100000
#define NUM_OH_THREADS ARR_SIZE

static int arr[ARR_SIZE] = {0};

static void *FillArr(void *arg)
{
	arr[(size_t) arg] = (size_t) arg;

	return NULL;
}

void Exc1(void)
{
	size_t i = 0;
	static pthread_t tid[NUM_OH_THREADS] = {0};

	for (i = 0; i < NUM_OH_THREADS; i++)
	{
		pthread_create(&tid[i], NULL, FillArr, (void *) i);
	}

	sleep(10);

	for (i = 0; i < ARR_SIZE; i++)
	{
		printf("%d\n", arr[i]);
	}

}


