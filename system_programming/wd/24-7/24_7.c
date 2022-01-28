#include <pthread.h>
#include <signal.h>			
#include <unistd.h> 
#include <stdio.h> 
#include <sys/types.h>  
#include "wd_lib.h" 
    

void ATM(void);

int main(int argc ,const char *argv[])
{
	MMI(argc, argv);
	ATM();
	DNR();

	return 0;
}

void ATM()
{
	int i = 0;
	printf("24/7 running\n");
	while (i<10)
	{
		printf("24/7 still running\n");
		sleep(5);
		++i;
	}
}


