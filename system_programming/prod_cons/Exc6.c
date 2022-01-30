#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include "pro_con.h"

#define NUM_OF_THREADS 5

typedef struct exc6
{
	size_t write; 
	pthread_mutex_t lock;
	sem_t semaphore;
	pthread_cond_t cond;
} exc6_t;

static void *Producer(void *param);
static void *Consumer(void *param);

void Exc6(void)
{
	pthread_t prod_tid = {0};
	pthread_t cons_tid[NUM_OF_THREADS] = {0};
	size_t i = 0;
	exc6_t *exc6 = NULL;

	exc6 = (exc6_t *)malloc(sizeof(exc6_t));
    if(!exc6)
    {
        exit(1);
    }

	exc6->write = 0;
    pthread_mutex_init(&exc6->lock, NULL);
	sem_init(&exc6->semaphore, 0, 0);
	pthread_cond_init(&exc6->cond, NULL);

    pthread_create(&prod_tid, NULL, Producer, exc6);
	for (i = 0; i < NUM_OF_THREADS; i++)
	{
		pthread_create(&cons_tid[i], NULL, Consumer, exc6);
	}

    pthread_join(prod_tid, NULL);
	for (i = 0; i < NUM_OF_THREADS; i++)
	{
		pthread_join(cons_tid[i], NULL);
	}

	free(exc6);

}

static void *Producer(void *param)
{
	size_t i = 0;
    exc6_t *exc6 = (exc6_t *) param;

	while (1)
	{		
		pthread_mutex_lock(&exc6->lock);
		exc6->write = rand() % 50;
        pthread_mutex_unlock(&exc6->lock);
        
        pthread_cond_broadcast(&exc6->cond);

		for (i = 0; i < NUM_OF_THREADS; ++i)
        {
            sem_wait(&exc6->semaphore);
        }

		printf("producer write is %lu\n", exc6->write);

        sleep(2);
	}

	return NULL;
}

static void *Consumer(void *param)
{
	exc6_t *exc6 = (exc6_t *) param;

	while (1)
	{
		size_t value = 0;
		
        pthread_mutex_lock(&exc6->lock);
        pthread_cond_wait(&exc6->cond,&exc6->lock); 
		value = exc6->write;
		
		sem_post(&exc6->semaphore);
		printf("consumer read is %lu\n", value);

	}

	return NULL;
}
