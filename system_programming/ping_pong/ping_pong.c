#define _POSIX_SOURCE	/* for sigaction() 	*/
#include <stdlib.h>		
#include <unistd.h>		/* for fork 		*/
#include <signal.h>		/* for signals		*/
#include <sys/types.h>	/* for pid_t	 	*/
#include <stdio.h>		


static pid_t pid = 0;
static void handler1(int signal);
static void handler2(int signal);

int main(void)
{
    struct sigaction act1 = {0};
    struct sigaction act2 = {0};
    
	act1.sa_handler = handler1;
	sigaction(SIGUSR1, &act1, NULL);

	act1.sa_handler = handler2;
	sigaction(SIGUSR2, &act2, NULL);
	
	pid = fork();

	if (0 != pid)	/* parent process */
	{
		kill(pid, SIGUSR1);
	}

	return 0;
}

static void handler1(int signal)
{
    pid_t pid_to_send = getppid();
	printf("Ping, my pid: %d\n", getpid());
	kill(pid_to_send, SIGUSR2);
}

static void handler2(int signal)
{
    pid_t pid_to_send = 0;
	printf("Pong, my pid: %d\n", getpid());
	kill(pid_to_send, SIGUSR1);
}


