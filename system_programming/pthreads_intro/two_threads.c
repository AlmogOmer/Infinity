#include <pthread.h>		/* for threads 		*/
#include <stdlib.h>			
#include <unistd.h>			/* for sleep		*/
#include <stdio.h>		

static void *Print1(void *arg);
static void *Print2(void *arg);

int main(void)
{
	static pthread_t thread_id[2] = {0};

	pthread_create(thread_id , NULL, Print1, NULL);
    pthread_create(thread_id + 1, NULL, Print2, NULL);

    pthread_join(*(thread_id), NULL);
    pthread_join(*(thread_id + 1), NULL);

	return 0;
}

static void *Print1(void *arg)
{
    size_t i = 0;
    (void)arg;

    while(i<30)
    {
        printf("Im thread 1\n");
        sleep (2);
        ++i;
    }

    return NULL;
}

static void *Print2(void *arg)
{
	size_t i = 0;
    (void)arg;

    while(i<30)
    {
        printf("Im thread 2\n");
        sleep (2);
        ++i;
    }

	return NULL;
}

