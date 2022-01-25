#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include "pro_con.h"
#include "singly_list.h"

#define NUM_OF_THREADS 5

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static sem_t semaphore;
static size_t counter = 0;

static void *Producer(void *param);
static void *Consumer(void *param);

void Exc3(void)
{
	pthread_t prod_tid[NUM_OF_THREADS] = {0};
	pthread_t cons_tid[NUM_OF_THREADS] = {0};
	size_t i = 0;
	slist_t *list = SListCreate();
	if (!list)
	{
		exit(1);
	}

	sem_init(&semaphore, 0, 0);

	for (i = 0; i < NUM_OF_THREADS; i++)
	{
		pthread_create(&prod_tid[i], NULL, Producer, list);
		pthread_create(&cons_tid[i], NULL, Consumer,  list);
	}

	for (i = 0; i < NUM_OF_THREADS; i++)
	{
		pthread_join(prod_tid[i], NULL);
		pthread_join(cons_tid[i], NULL);
	}

	SListDestroy(list);

}

static void *Producer(void *param)
{
	while (counter < 50)
	{
		pthread_mutex_lock(&lock);
		SListInsert(SListEnd(param),&counter); 
		pthread_mutex_unlock(&lock);

        sem_post(&semaphore);
		++counter;
		sleep(2);
	}

	return NULL;
}

static void *Consumer(void *param)
{   
	
	while (1)
	{
		sem_wait(&semaphore);
		pthread_mutex_lock(&lock);
		
		if (SListCount(param))
		{
			int value = *(int*) SListIterGetData(SListBegin(param));
            printf("VALUE : %d\n", value);
			
			SListRemove(SListBegin(param));
			printf("LIST SIZE : %lu\n", SListCount(param));
		}

        pthread_mutex_unlock(&lock);
	}

	return NULL;
}

