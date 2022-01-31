#include <unistd.h> 
#include <stdio.h>       
#include "wd_lib.h"

void WD(void);

int main(int argc ,char *argv[])
{
	if ( -1 == MMI(argc, argv))
	{
		return 1;
	}
	
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
    
    

