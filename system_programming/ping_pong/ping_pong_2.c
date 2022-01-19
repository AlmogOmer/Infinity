#define _POSIX_SOURCE	/* for sigaction() 	*/
#include <stdlib.h>		
#include <unistd.h>		/* for fork 		*/
#include <signal.h>		/* for signals		*/
#include <sys/types.h>	/* for pid_t	 	*/
#include <stdio.h>	

static void Action1(int signal, siginfo_t *info, void *context);
static void Action2(int signal, siginfo_t *info, void *context);

int main(int argc, char const *argv[])
{
	struct sigaction act1 = {0};
    struct sigaction act2 = {0};

    act1.sa_sigaction = Action1;
    act1.sa_flags = SA_SIGINFO;
    sigemptyset(&act1.sa_mask);
    sigaction(SIGUSR1, &act1, NULL);

    act2.sa_sigaction = Action2;
    act2.sa_flags = SA_SIGINFO;
    sigemptyset(&act2.sa_mask);
    sigaction(SIGUSR2, &act2, NULL);
    
    if (argc > 1)
    {
        pid_t pid_ping = (pid_t) atoi(argv[1]);
        kill(pid_ping, SIGUSR1);
    }

    else
    {
        sleep(500);
    }
    
	while (1);

	return 0;
}


static void Action1(int signal, siginfo_t *info, void *context)
{
	(void)signal;
    (void)context;
    printf("pong\n");
	kill(info->si_pid, SIGUSR2);
}

static void Action2(int signal, siginfo_t *info, void *context)
{
	(void)signal;
    (void)context;
    printf("ping\n");
	kill(info->si_pid, SIGUSR1);
}

