#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "pro_con.h"

#define SIZE 30
#define UNUSED(x) (void)(x)

static volatile int is_busy = 0;
static int buf = 0;

static void *Producer(void *arg);
static void *Consumer(void *arg);

void Exc1(void)
{
    pthread_t prod_tid = 0;
    pthread_t cons_tid = 0;

    pthread_create(&prod_tid, NULL, Producer, NULL);
    pthread_create(&cons_tid, NULL, Consumer,  NULL);

	pthread_join(prod_tid, NULL);
	pthread_join(cons_tid, NULL);
}

static void *Producer(void *arg)
{
    int i = 0;
    int write; 
    UNUSED(arg);
    
	while(i < SIZE)
	{
		write = rand() % SIZE;
        while (__atomic_load_n(&is_busy, __ATOMIC_SEQ_CST) != 0);

        printf("producer wrote : %d\n", write);

		__atomic_store_n(&buf,write,__ATOMIC_SEQ_CST);

        is_busy = 1;

        ++i;
	}

    return NULL;
}

static void *Consumer(void *arg)
{
    int i = 0;
    UNUSED(arg);
    
	while(i < SIZE)
	{
        while (__atomic_load_n(&is_busy, __ATOMIC_SEQ_CST) != 1);

        printf("producer read : %d\n", buf);

        is_busy = 0;

        ++i;
	}

    return NULL;
}

