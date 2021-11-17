#include "priority_queue.h"
#include "../sorted_list/sorted_list.h"
#include <stdlib.h>
#include <assert.h>

struct Pri_Queue
{
	sorted_list_t *list;
};

typedef struct Pri_Queue pri_queue_t;

typedef int (*compare_func_t)(const void *new_elem, const void *curr_elem, const void *param);
typedef int(*is_match_t)(const void *curr_item, const void *param);

/*creat new pri_queue*/
pri_queue_t *PriQueueCreate(compare_func_t cmp_func, const void *param)
{
	pq_t *new_pq = NULL;
	
	new_pq = (pri_queue_t *) malloc(sizeof(pri_queue_t));
	if (NULL == new_pq)
	{
		return NULL;
	}
	
	new_pq->list = SortedListCreate(cmp_func, param);
	if (NULL == new_pq->list)
	{
		free(new_pq);
		return NULL;
	}
	
	return new_pq;

}
/*destroy pri_queue*/
void PriQueueDestroy(pri_queue_t *pri_queue)
{

	assert(pri_queue);
	
	SortedListDestroy(pri_queue->list);
	free(pri_queue);

}

/* insert new item to back of the pri_queue */
int PriQueueEnqueue(pri_queue_t *pri_queue, const void *data)
{
	sorted_list_iter_t iter;
	assert(pri_queue);
	SortedListInsert(pri_queue->list, data);
	
	iter=SortedListFind(SortedListBegin(pri_queue->list), SortedListEnd(pri_queue->list), data);
	return SortedListIterIsEqual(iter,SortedListEnd(pri_queue->list));


}

/* pop item from the front of the pri_queue*/
void PriQueueDequeue(pri_queue_t *pri_queue)
{
	sorted_list_iter_t iter popped_iter;
	assert(pri_queue && !PriQueueIsEmpty(pri_queue));
	

	popped_itet.list = pri_queue->list;
	popped_iter = SortedListBegin(list);
	
	
	SortedListRemove(popped_iter);
	

}

/*get value of the front item of the pri_queue*/
void *PriQueuePeek(const pri_queue_t *pri_queue)
{ 
	assert(pri_queue && !PriQueueIsEmpty(pri_queue));
	
	return SortedListIterGetData(SortedListBegin(pri_queue->list));

}
/*return the sizeof pri_queue*/
size_t PriQueueSize(const pri_queue_t *pri_queue)
{
	assert(pri_queue);
	
	return SortedListSize(pri_queue->list);

}

/*check if pri_queue is empty*/
extern int PriQueueIsEmpty(const pri_queue_t *pri_queue);	/* return value empty - 1, not empty - 0 */

/*remove all elements*/
extern void PriQueueClear(pri_queue_t *pri_queue);

/*remove elements with a certain UID*/
extern void PriQueueErase(pri_queue_t *pri_queue, is_match_t match_func, const void *param);

