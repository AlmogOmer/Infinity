#include "scheduler.h"
#include "task.h"
#include <stdlib.h>	/* for malloc */
#include <assert.h>	/* for assertions */
#include <unistd.h>	/* for sleep */
#include "priority_queue.h"


#define UNUSED(x) (void)(x)

struct scheduler
{
	pri_queue_t *task_queue;
	unsigned int stop_flag;

};


static int IsPrior(const void *data1, const void *data2, const void *param)
{
	assert(data1 && data2);
	UNUSED(param);
	
	return TaskGetExecTime(data2) - TaskGetExecTime(data1);
}
/*creates new scheduler engine*/
scheduler_t *SchedulerCreate()
{
	int param = 1;
	scheduler_t *sch = (scheduler_t *) malloc(sizeof(scheduler_t));
	if (!sch)
	{
		return NULL;
	}
	
	sch->task_queue = PriQueueCreate(IsPrior, &param);
	if (!sch->task_queue)
	{
		free(sch);
		return NULL;
	}
	
	sch->stop_flag = 0;
	return sch;

}

/*destroy scheduler*/
void SchedulerDestroy(scheduler_t *scheduler)
{
	/* free all nodes and tasks stored in them */
	while (!SchedulerIsEmpty(scheduler))
	{
		free(PriQueuePeek(scheduler->task_queue));
		PriQueueDequeue(scheduler->task_queue);	
	}
	
	/* free the empty queue */
	PriQueueDestroy(scheduler->task_queue);
	
	/* free the control block */
	free(scheduler);


}

/* insert new task to the scheduler engine*/
unique_id_t SchedulerTaskAdd(scheduler_t *scheduler, task_func_t task, 
						size_t interval_in_secs, void *param)
{
	task_t *added_task = NULL;
	
	added_task = TaskCreate(task, param, interval_in_secs);
	if (added_task == NULL)
	{
		return uid_null_uid;
	}
	
	PriQueueEnqueue(scheduler->task_queue, added_task);
	
	return TaskGetUID(added_task);

}

/* remove task from scheduler engine*/
void SchedulerTaskCancel(scheduler_t *scheduler, unique_id_t uid)
{
	PriQueueErase(scheduler->task_queue, &uid, TaskIsSameUID, NULL);

}

/* run the scheduler engine */
int SchedulerRun(scheduler_t *scheduler)
{
	task_t *next_task = NULL;
	
	assert(scheduler);
	assert(!SchedulerIsEmpty(scheduler));
	
	while (!(scheduler->stop_flag))
	{
		if (SchedulerIsEmpty(scheduler))
		{
			return 0;
		}
		
		next_task = PriQueuePeek(scheduler->task_queue);
		
		sleep(TaskGetExecTime(next_task) - time(NULL));
		
		PriQueueDequeue(scheduler->task_queue);
		
		if (TaskExecute(next_task))	 /* task continues */
		{
			TaskUpdateExecTime(next_task);
			
			/*task uid will remain the same */
			PriQueueEnqueue(scheduler->task_queue, next_task); 
			
			/*SchedulerTaskAdd(scheduler, next_task->task_func, 
						next_task->interval_in_secs, next_task->params);*/
			
		}
		else
		{
			TaskDestroy(next_task);
		}
		
		
	}
	
	return 1;


}

/* stop running scheduler */
void SchedulerStop(scheduler_t *scheduler)
{
	assert(scheduler);
	
	scheduler->stop_flag = 1;

}

/* return the size of the scheduler */
size_t SchedulerSize(scheduler_t *scheduler)
{
	assert(scheduler);
	
	return PriQueueSize(scheduler->task_queue);
}

/*check if scheduler is empty*/
int SchedulerIsEmpty(scheduler_t *scheduler)
{
	assert(scheduler);
	
	return PriQueueIsEmpty(scheduler->task_queue);

}

/*stop the scheduler*/
void SchedulerClear(scheduler_t *scheduler)
{
	assert(scheduler);
	
	while (!SchedulerIsEmpty(scheduler))
	{
		free(PriQueuePeek(scheduler->task_queue));
		PriQueueDequeue(scheduler->task_queue);	
	}

}


