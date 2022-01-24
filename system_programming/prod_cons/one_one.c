#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <stdatomic.h>

#define ARR_SIZE 50
#define UNUSED(x) (void)(x)

static atomic_int is_busy = 0;
static int arr[ARR_SIZE] = {0};
static int counter = 0;

static void *Producer(void *arg);
static void *Consumer(void *arg);

int main(void)
{
    pthread_t prod_tid = 0;
    pthread_t cons_tid = 0;

    pthread_create(&prod_tid, NULL, Producer, NULL);
    pthread_create(&cons_tid, NULL, Consumer,  NULL);

	pthread_join(prod_tid, NULL);
	pthread_join(cons_tid, NULL);

    return 0;
}

static void *Producer(void *arg)
{
    int i = 0;
    UNUSED(arg);
    
	while (counter < ARR_SIZE)
	{
		while (is_busy);

		is_busy = 1;
        printf("in producer\n");

		for (i = 0; i < ARR_SIZE; ++i)
		{
			arr[i] = counter;
		}

		++counter;

		is_busy = 0;
	}

    return NULL;
}

static void *Consumer(void *arg)
{
    int value = 0;
    int i = 1;
    UNUSED(arg);
    
	while (counter < ARR_SIZE)
	{
		while (is_busy);

		is_busy = 1;
        printf("in consumer\n");

		value = arr[0];
		for (i = 1; i < ARR_SIZE; ++i)
		{
            if (arr[i] != value)
			{
				printf("failed for value %d in index %d\n", value, i);
				break;
			}
		}

		is_busy = 0;
	}

    return NULL;
}

