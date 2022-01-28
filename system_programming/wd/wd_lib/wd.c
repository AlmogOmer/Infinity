#include <pthread.h>
#include <signal.h>			
#include <unistd.h> 
#include <stdio.h> 
#include <sys/types.h>        
#include "wd_lib.h"

void WD(void);

int main(int argc ,const char *argv[])
{
	MMI(argc, argv);
	WD();

	return 0;
}

void WD()
{
	printf("WD running\n");
	while (1)
	{
		printf("WD still running\n");
		sleep(5);
	}
}
    
    

