#include "task.h"
#include "../uid/uid.h"
#include <time.h>	/* for time() */
#include <assert.h>	/* for assertions */


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



void TaskDestroy(task_t *task)
{
	assert(task);
	
	free(task);
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


int TaskIsSameUID(void* task1, void* param)
{
	if (UIDIsEqual(((task_t*)task1)->uid, *((unique_id_t*)param)))
	{
		free((task_t*)task1);
		return 1;
	}
	
	return 0;
}

unique_id_t TaskGetUID(const task_t *task)
{
	assert(task);
	
	return (task->uid);

}



