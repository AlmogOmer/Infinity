#define _POSIX_SOURCE	/* for sigaction() 	*/
#include <stdlib.h>		
#include <unistd.h>		/* for fork 		*/
#include <signal.h>		/* for signals		*/
#include <sys/types.h>	/* for pid_t	 	*/
#include <stdio.h>		

static pid_t pid_child = 0;
static pid_t pid_parent = 0;
static void handler1(int signal);
static void handler2(int signal);

int main(void)
{
    struct sigaction act1 = {0};
    struct sigaction act2 = {0};
    
	act1.sa_handler = handler1;
	sigemptyset(&act1.sa_mask);
	sigaction(SIGUSR1, &act1, NULL);

	act2.sa_handler = handler2;
	sigemptyset(&act2.sa_mask);
	sigaction(SIGUSR2, &act2, NULL);
	
	pid_parent = getpid();
	pid_child = fork();

	if (0 < pid_child) /* parent process */
	{
		kill(pid_child, SIGUSR1);
		wait(NULL);
	}

	while(1);
	
	return 0;
}

static void handler1(int signal)
{
	printf("Ping, my pid: %d\n", getpid());
	kill(pid_parent, SIGUSR2);
}

static void handler2(int signal)
{
	printf("Pong, my pid: %d\n", getpid());
	kill(pid_child, SIGUSR1);
}


