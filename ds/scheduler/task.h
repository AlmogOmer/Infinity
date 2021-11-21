#ifndef TASK_H
#define TASK_H

/* this module provide creation and operations on periodic tasks */

#include <stdlib.h>
#include "../uid/uid.h"

/* return value- 0 for abort and 1 for continue executing */

typedef int (*task_func_t)(const void* param);

typedef struct task task_t;

extern task_t *TaskCreate(task_func_t task_func, void *params, time_t interval_in_secs);

extern void TaskDestroy(task_t *task);

extern time_t TaskGetExecTime(const task_t *task);

extern void TaskUpdateExecTime(task_t *task);

/* return value- 0 abort and 1 for continue looping */
extern int TaskExecute(task_t *task);

extern int TaskIsSameUID(void* task1, void* param);

extern unique_id_t TaskGetUID(const task_t *task);

#endif
