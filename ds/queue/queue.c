#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "queue.h"
#include "../s_list/singly_list.h"

struct Queue
{
	slist_t *list;
};


/*creat new queue*/
queue_t *QueueCreate(void)
{
	queue_t *new_queue = NULL;
	new_queue = (queue_t*)malloc(sizeof(queue_t));
	if (new_queue == NULL)
	{
		return NULL;
	}
	new_queue->list = SListCreate();
	
	return new_queue;

}

/*destroy queue*/
void QueueDestroy(queue_t *queue)
{
	assert(queue);
	SListDestroy(queue->list);
	queue->list = NULL;
	free(queue);

}

/* insert new item to back of the queue */
void QueueEnqueue(queue_t *queue, const void *val)
{
	assert(queue);
	SListInsert(SListEnd(queue->list), val);
}

/* pop item from the front of the queue*/
void QueueDequeue(queue_t *queue)
{
	assert(queue);
	SListRemove(SListBegin(queue->list));
}

/*get value of the front item of the queue*/
extern void *QueuePeek(const queue_t *queue)
{
	assert(queue);
	return SListIterGetData(SListBegin(queue->list));
} 

/*return the sizeof queue*/
extern size_t QueueSize(const queue_t *queue)
{
	assert(queue);
	return SListCount(queue->list);
}

/*check if queue is empty*/
extern int QueueIsEmpty(const queue_t *queue)
{
	assert(queue);
	return (0 == SListCount(queue->list));
}


