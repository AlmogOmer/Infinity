#include "scheduler.h"
#include <stdlib.h>	/* for malloc */
#include <assert.h>	/* for assertions */
#include <unistd.h>	/* for sleep */
#include <time.h>	/* for time */
#include "../uid/uid.h"
#include "../pri_queue/priority_queue.h"
#include "../sorted_list/sorted_list.h"

struct scheduler
{
	pri_queue_t *task_queue;

};
struct task 
{
	unique_id_t uid;
	task_func_t task_func;
	void *params;
	time_t interval_in_secs;
	time_t execute_time;
};

task_t *TaskCreate(task_func_t task_func, void *params, time_t interval_in_secs)
{
	task_t *task = NULL;
	
	
	task = (task_t *) malloc(sizeof(task_t));
	if (!task)
	{
		return NULL;
	}
	
	task->uid = UIDGenerate();
	task->task_func = task_func;
	task->params = params;
	task->interval_in_secs = interval_in_secs;
	task->execute_time = time(NULL) + interval_in_secs;
	
	return task;
}

time_t TaskGetExecTime(const task_t *task)
{
	
	return (task->execute_time);
}

void TaskUpdateExecTime(task_t *task)
{
	
	task->execute_time += task->interval_in_secs;
}

/* return value- 0 abort and 1 for continue looping */
int TaskExecute(task_t *task)
{
	assert(task);
	
	return (task->task_func(task->params));
}

int TaskIsSame(void* task1, void* task2)
{
	
	return (UIDIsEqual(((task_t*)task1)->uid, ((task_t*)task2)->uid));
}

static int IsPrior(const void *data1, const void *data2, const void *param)
{
	assert(data1 && data2);

	
	if(*(int*)param == 1)
	{
		return TaskGetExecTime(data1) < TaskGetExecTime(data2);
	}
	return TaskGetExecTime(data1) > TaskGetExecTime(data2);

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
	
	
	return sch;

}

/*destroy scheduler*/
void SchedulerDestroy(scheduler_t *scheduler)
{
	/* free all nodes and tasks stored in them */
	while (!SchedulerIsEmpty(scheduler))
	{
		free(PriQueuePeek(scheduler->task_queue));	
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
	
	PriQueueEnqueue(scheduler->task_queue, added_task);
	
	return (added_task->uid);

}

/* remove task from scheduler engine*/
void SchedulerTaskCancel(scheduler_t *scheduler, unique_id_t uid)
{
	PriQueueErase(scheduler->task_queue, TaskIsSame, &uid);

}

/* run the scheduler engine */
int SchedulerRun(scheduler_t *scheduler)
{
	task_t *next_task = NULL;
	
	assert(scheduler);
	assert(!SchedulerIsEmpty(scheduler));
	
	while (1)
	{
		if (SchedulerIsEmpty(scheduler))
		{
			return 0;
		}
		
		next_task = PriQueuePeek(scheduler->task_queue);
		
		sleep(TaskGetExecTime(next_task) - time(NULL));
		
		PriQueueDequeue(scheduler->task_queue);
		
		if (next_task->task_func(next_task->params))		/* task continues */
		{
			TaskUpdateExecTime(next_task);
			SchedulerTaskAdd(scheduler, next_task->task_func, 
						next_task->interval_in_secs, next_task->params);
			
		}
		else
		{
			free(next_task);
		}
		
		
	}
	
	return 1;


}

/* stop running scheduler */
extern void SchedulerStop(scheduler_t *scheduler);

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
extern void SchedulerClear(scheduler_t *scheduler);


