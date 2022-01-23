#include <stdio.h>
#include <stdlib.h>	  
#include <semaphore.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	sem_t *sema;
	int VALUE = 4;
	size_t i = 0;
	int val = 0;
	
	if (argc > 1)
	{
		sema = sem_open(argv[1], O_CREAT, 0666, VALUE);
        sem_getvalue(sema, &val);
        printf("sem initial value: %d\n", val);
        
		switch (argv[2][0])
		{
		case 'D':
			for (i = 0; i < (size_t)atoi(argv[3]); ++i)
			{
				sem_wait(sema);
			}

            sem_getvalue(sema, &val);
            printf("value after wait(decrement): %d\n", val);
			break;

		case 'I':
			for (i = 0; i < (size_t)atoi(argv[3]); ++i)
			{
				sem_post(sema);
			}
            sem_getvalue(sema, &val);
            printf("value after post(increment): %d\n", val);
			break;

		case 'V':
			sem_getvalue(sema, &val);
			printf("show value: %d\n", val);
			break;

		case 'X':
			sem_close(sema);
			sem_unlink(argv[1]);
			exit(1);
			break;
		}
	}

	return 0;
}


