#include <pthread.h>		/* for threads 		*/
#include <stdlib.h>			
#include <unistd.h>			/* for sleep		*/
#include <stdio.h>		

static void *Print(void *arg);

int main(void)
{
	static pthread_t thread_id[2] = {0};
    char *arg1 = "Im thread 1";
    char *arg2 = "Im thread 2";

	pthread_create(thread_id , NULL, Print, arg1);
    pthread_create(thread_id + 1, NULL, Print, arg2);

    pthread_join(*(thread_id), NULL);
    pthread_join(*(thread_id + 1), NULL);

	return 0;
}

static void *Print(void *arg)
{
    size_t i = 0;
    while(i<30)
    {
        printf("%s\n", (char *)arg);
        sleep (2);
        ++i;
    }

    return NULL;
}



