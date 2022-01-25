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
	size_t read; /*consumer index*/
	size_t write; /*producer index*/
	pthread_mutex_t lock;
	sem_t semaphore;
	pthread_cond_t cond;
	size_t counter;
} fsq_t;

static void *Producer(void *param);
static void *Consumer(void *param);

void Exc6(void)
{
	pthread_t prod_tid = {0};
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
    pthread_mutex_init(&fsq->lock, NULL);
	sem_init(&fsq->semaphore, 0, 0);
	pthread_cond_init(&fsq->cond, NULL);
	fsq->counter = 0;

    pthread_create(&prod_tid, NULL, Producer, fsq);
	for (i = 0; i < NUM_OF_THREADS; i++)
	{
		pthread_create(&cons_tid[i], NULL, Consumer, fsq);
	}

    pthread_join(prod_tid, NULL);
	for (i = 0; i < NUM_OF_THREADS; i++)
	{
		pthread_join(cons_tid[i], NULL);
	}

	free(fsq);

}

static void *Producer(void *param)
{
	size_t i = 0;
    fsq_t *fsq = (fsq_t *) param;

	while (fsq->counter < 50)
	{
        pthread_mutex_lock(&fsq->lock);
		fsq->queue[fsq->write] = fsq->counter;
		fsq->write = (fsq->write + 1) % QUEUE_SIZE;
        pthread_mutex_unlock(&fsq->lock);
        
        fsq->counter += 1;
        
        for (i = 0; i < NUM_OF_THREADS; ++i)
        {
            sem_post(&fsq->semaphore);
        }
        
        pthread_cond_broadcast(&fsq->cond);

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
		sem_wait(&fsq->semaphore);
		
        pthread_mutex_lock(&fsq->lock);
        pthread_cond_wait(&fsq->cond,&fsq->lock); 
		value = fsq->queue[fsq->read];
		fsq->read = (fsq->read + 1) % QUEUE_SIZE;
		pthread_mutex_unlock(&fsq->lock);

		printf("value is %d\n", value);

	}

	return NULL;
}
