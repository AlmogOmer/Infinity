#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include "pro_con.h"

#define QUEUE_SIZE 50
#define NUM_OF_THREADS 5

typedef struct fsq
{
	int queue[QUEUE_SIZE];
	size_t read;
	size_t write;
	pthread_mutex_t prod_lock;
	pthread_mutex_t cons_lock;
	sem_t is_full;
	sem_t is_empty;
	size_t counter;
} fsq_t;

static void *Producer(void *param);
static void *Consumer(void *param);

void Exc5(void)
{
	pthread_t prod_tid[NUM_OF_THREADS] = {0};
	pthread_t cons_tid[NUM_OF_THREADS] = {0};
	size_t i = 0;
	fsq_t *fsq = NULL;

	fsq = (fsq_t *)malloc(sizeof(fsq_t));
    if(!fsq)
    {
        exit(1);
    }

	fsq->read = 0;
	fsq->write = 0;
	pthread_mutex_init(&fsq->prod_lock, NULL);
	pthread_mutex_init(&fsq->cons_lock, NULL);
	
    sem_init(&fsq->is_full, 0, QUEUE_SIZE);
	sem_init(&fsq->is_empty, 0, 0);
	fsq->counter = 0;

	for (i = 0; i < NUM_OF_THREADS; i++)
	{
		pthread_create(&prod_tid[i], NULL, Producer, fsq);
		pthread_create(&cons_tid[i], NULL, Consumer, fsq);
	}

	for (i = 0; i < NUM_OF_THREADS; i++)
	{
		pthread_join(prod_tid[i], NULL);
		pthread_join(cons_tid[i], NULL);
	}

	free(fsq);

}

static void *Producer(void *param)
{
	fsq_t *fsq = (fsq_t *) param;

	while (fsq->counter < 50)
	{
		sem_wait(&fsq->is_full);
		
		pthread_mutex_lock(&fsq->prod_lock);
		fsq->queue[fsq->write] = fsq->counter;
		fsq->write = (fsq->write + 1) % QUEUE_SIZE;
        pthread_mutex_unlock(&fsq->prod_lock);

		sem_post(&fsq->is_empty);
		fsq->counter += 1;
		sleep(2);
	}

	return NULL;
}

static void *Consumer(void *param)
{
	fsq_t *fsq = (fsq_t *) param;

	while (1)
	{
		int value = 0;
		sem_wait(&fsq->is_empty);
		
        pthread_mutex_lock(&fsq->cons_lock);
		value = fsq->queue[fsq->read];
		fsq->read = (fsq->read + 1) % QUEUE_SIZE;
        pthread_mutex_unlock(&fsq->cons_lock);

		sem_post(&fsq->is_full);
		printf("value is %d\n", value);
	}

	return NULL;
}


