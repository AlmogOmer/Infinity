#include <stdlib.h>			
#include <sys/time.h>		
#include <stdio.h>			
#include "th_100k.h"	

#define ARR_SIZE 100000

static int arr[ARR_SIZE] = {0};

void Exc6(void)
{
	size_t i = 0;
	struct timeval start = {0};
	struct timeval end = {0};
	double total_time = 0;

	gettimeofday(&start, NULL);

	#pragma omp parallel for
	for (i = 0; i < ARR_SIZE; i++)
	{
		arr[i] = i;
	}

	gettimeofday(&end, NULL);

	total_time = ((end.tv_sec - start.tv_sec) * 1000000);
	total_time += (end.tv_usec - start.tv_usec);

	printf("total time is %f micro-seconds\n", total_time);

	for (i = 0; i < ARR_SIZE; i++)
	{
		/*printf("index %lu has value of %d\n", i, arr[i]);*/
		if ((int)i != arr[i])
		{
			printf("array is not ok in index %lu\n", i);
		}
	}
}
