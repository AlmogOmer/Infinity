#include <unistd.h> 
#include <stdio.h> 
#include "wd_lib.h" 
    

void ATM(void);

int main(int argc ,char *argv[])
{
	if ( -1 == MMI(argc, argv))
	{
		return 1;
	}
	
	ATM();
	
	return 0;
}

void ATM()
{
	int i = 0;
	printf("24/7 running\n");
	while (i < 10)
	{
		printf("24/7 still running\n");
		sleep(5);
		++i;
	}
	/*DNR();*/
}


