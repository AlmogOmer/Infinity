#include <pthread.h>        
#include <signal.h>			
#include <unistd.h>         
#include "wd_lib.h"
#include "scheduler.h"
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <semaphore.h>

#define _GNU_SOURCE

static int flag = 0;
static pid_t other_pid = 0;
static scheduler_t *scheduler = NULL;
static sem_t *ready = NULL;

static void SIGUSR1Handler(int signal, siginfo_t *info, void *context);
static void SIGUSR2Handler(int signal, siginfo_t *info, void *context);
void *StartRoutine(void *params);
static int SendSignalTask(const void *param);
static int CheckSignalTask(const void *param);
void DNR(void);

int MMI(int argc, char *argv[])
{
    unique_id_t uid = uid_null_uid;
	pthread_t tid = 0;
	char *args[2] = {"../wd/wd.out", NULL};
    struct sigaction act = {0};
    (void)argc;
	
    act.sa_sigaction = SIGUSR1Handler;
    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    sigaction(SIGUSR1, &act, NULL);

	act.sa_sigaction = SIGUSR2Handler;
    act.sa_flags = SA_SIGINFO;
    sigemptyset(&act.sa_mask);
    sigaction(SIGUSR2, &act, NULL);

	if (NULL == getenv("en_wd"))
    {
        setenv("en_wd", "../wd/wd.out", 1);
        other_pid = fork();

		if (other_pid == -1)
		{
			return -1;
		}

        else if (other_pid == 0)
        {	/* child process */
            setenv("en_wd", argv[0], 1);
			if (-1 == execv(args[0],args))
			{
				/*kill(other_pid, SIGTERM);*/
			}
        }
	}

	else if (other_pid > 0)
	{
		sem_wait(ready);
	}

    scheduler = SchedulerCreate();
	if(!scheduler)
	{
		return -1;
	}

	uid = SchedulerTaskAdd(scheduler, SendSignalTask, 1, NULL);
	if (UIDIsEqual(uid, uid_null_uid))
	{
		SchedulerDestroy(scheduler);
		return -1;
	}

	uid = SchedulerTaskAdd(scheduler, CheckSignalTask, 3, argv[0]);
	if (UIDIsEqual(uid, uid_null_uid))
	{
		SchedulerDestroy(scheduler);
		return -1;
	}

	sem_post(ready);
    pthread_create(&tid, NULL, StartRoutine, argv[0]);

	return 1;
	
}

void DNR(void)
{
	kill(getpid(), SIGUSR2);
	kill(other_pid, SIGUSR2);

	sem_unlink("ready");
}

static void SIGUSR1Handler(int signal, siginfo_t *info, void *context)
{
	(void)signal;
	(void)context;

	flag = 1;
	other_pid = info->si_pid;
}

static void SIGUSR2Handler(int signal, siginfo_t *info, void *context)
{
    (void)signal;
	(void)context;
	(void)info;

	SchedulerStop(scheduler);
}

void *StartRoutine(void *param)
{
	(void)param;
	SchedulerRun(scheduler);

	SchedulerDestroy(scheduler);
	
	sem_close(ready);

	return NULL;
}

static int SendSignalTask(const void *param)
{
	(void)param;
	kill(other_pid, SIGUSR1);
	return 1;
}

static int CheckSignalTask(const void *param)
{
	char *recover = getenv("en_wd");
	char *args[2] = {0};

	if (flag)
	{
		flag = 0;
		return 1;
	}

	printf("process: %d is dead, resuscitating.. \n", other_pid);
	
	other_pid = fork();

	if (other_pid == -1)
	{
		return 0;
	}

	else if (other_pid == 0)
	{	
		setenv("en_wd", param, 1);
		args[0] = recover;
		if (-1 == execv(args[0],args))
		{
			/*kill(other_pid, SIGTERM);*/
		}
		
	}

	else
	{
		sem_wait(ready);
	}

	return 1;
}
