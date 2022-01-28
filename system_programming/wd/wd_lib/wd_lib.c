#include <pthread.h>        
#include <signal.h>			
#include <unistd.h>         
#include "wd_lib.h"
#include "scheduler.h"
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>

static int flag = 0;
static pid_t pid = 0;
volatile sig_atomic_t wd_running = 0;
static scheduler_t *scheduler = NULL;
static sem_t *ready = NULL;

static void SIGUSR1Handler(int signal, siginfo_t *info, void *context);
static void SIGUSR2Handler(int signal, siginfo_t *info, void *context);
void *StartRoutine(void *params);
static int SendSignalTask(const void *param);
static int CheckSignalTask(const void *param);
void DNR(void);

void MMI(int argc, const char *argv[])
{
    pthread_t tid = 0;
    char *args[2] = {"../wd_lib/wd.out", NULL};
    struct sigaction act1 = {0};
	struct sigaction act2 = {0};
	ready = sem_open("ready", O_CREAT, 0666, 0);
    (void)argc;
	
    act1.sa_sigaction = SIGUSR1Handler;
    act1.sa_flags = SA_SIGINFO;
    sigemptyset(&act1.sa_mask);
    sigaction(SIGUSR1, &act1, NULL);

	act2.sa_sigaction = SIGUSR2Handler;
    act2.sa_flags = SA_SIGINFO;
    sigemptyset(&act2.sa_mask);
    sigaction(SIGUSR2, &act2, NULL);

    if (NULL == getenv("en_wd"))
    {
        setenv("en_wd", argv[0], 1);
        pid = fork();

        if (pid == 0)
        {	/* child process */
            execvp(args[0],args);
        }

		else
		{
			sem_wait(ready);
		}
    }

	if (0 == strcmp(argv[0], "../wd_lib/wd.out"))
	{
		wd_running = 1;
	}

	else
	{
		wd_running = 0;
	}
    
	sem_post(ready);
    pthread_create(&tid, NULL, StartRoutine, NULL);
	
}

void DNR(void)
{
	if (wd_running)
    {
        kill(pid, SIGUSR2);
        wd_running = 0;
    }

	else
	{
		kill(pid, SIGUSR2);
	}

}


static void SIGUSR1Handler(int signal, siginfo_t *info, void *context)
{
	(void)signal;
	(void)context;

	flag = 1;
	pid = info->si_pid;
}

static void SIGUSR2Handler(int signal, siginfo_t *info, void *context)
{
    (void)signal;
	(void)info;
	(void)context;
	
	kill(pid, SIGUSR2);

	SchedulerStop(scheduler);
	SchedulerDestroy(scheduler);
	abort();

}

void *StartRoutine(void *param)
{
	scheduler = SchedulerCreate();
	(void)param;

	SchedulerTaskAdd(scheduler, SendSignalTask, 1, NULL);
	SchedulerTaskAdd(scheduler, CheckSignalTask, 3, NULL);

	SchedulerRun(scheduler);

	atexit(DNR);

	return NULL;
}

static int SendSignalTask(const void *param)
{
	(void)param;
	kill(pid, SIGUSR1);
	return 1;
}

static int CheckSignalTask(const void *param)
{
	char *args[2] = {"../wd_lib/wd.out", NULL};
	(void)param;
	
	if (flag)
	{
		flag = 0;
		return 1;
	}

	printf ("process: %d is dead, resuscitating.. \n", pid);

	pid = fork();

	if (pid == 0)
	{	
		if (wd_running) /*247 is dead*/
		{
			args[0] = getenv("en_wd");
			execvp(args[0],args);
			sem_post(ready);
		}

		else /*wd is dead*/
		{
			wd_running = 1;
			execvp(args[0],args);
			sem_post(ready);
		}
		
	}

	else
	{
		sem_wait(ready);
	}

	return 1;
}
