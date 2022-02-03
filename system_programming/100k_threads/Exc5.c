#include <pthread.h>		/* for threads 		*/
#include <stdlib.h>			
#include <sys/time.h>		/* for time 		*/
#include <unistd.h>			/* for sleep		*/
#include <stdio.h>		
#include "th_100k.h"	

#define ARR_SIZE 100000

static int arr[ARR_SIZE] = {0};
static int thread_part = 1;

static void *FillArr(void *arg)
{
	size_t i = ((size_t) arg) * (thread_part);
	size_t max = i + thread_part;

	for (; i < max; i++)
	{
		arr[i] = (int) i;
	}
	
	return NULL;
}

void Exc5(void)
{
	size_t i = 0;
	int num_of_threads = 8;
	pthread_t *tid = NULL;
	struct timeval start = {0};
	struct timeval end = {0};
	double total_time = 0;

	thread_part = (ARR_SIZE / num_of_threads);
	
	tid = (pthread_t *) malloc(num_of_threads * sizeof(pthread_t));
	if (!tid)
	{
		exit(1);
	}

	gettimeofday(&start, NULL);

	for (i = 0; i < num_of_threads; i++)
	{
		if (pthread_create(tid + i, NULL, FillArr, (void *) i))
		{
            printf("thread create has an error");
		}
	}
	
	for (i = 0; i < num_of_threads; i++)
	{
		if (pthread_join(tid[i], NULL))
		{
            printf("thread join has an error");
		}
	}

	gettimeofday(&end, NULL);

	total_time = ((end.tv_sec - start.tv_sec) * 1000000);
	total_time += (end.tv_usec - start.tv_usec);

	printf("total time for %d threads is %f micro-seconds\n", num_of_threads, total_time);

	for (i = 0; i < ARR_SIZE; i++)
	{
		/*printf("index %lu has value of %d\n", i, arr[i]);*/
		if ((int)i != arr[i])
		{
			printf("array is not ok in index %lu\n", i);
		}
	}

	free(tid);

}