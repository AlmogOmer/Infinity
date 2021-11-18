#include "priority_queue.h"
#include "../sorted_list/sorted_list.h"
#include <stdlib.h>
#include <assert.h>

struct Pri_Queue
{
	sorted_list_t *list;
};


/*creat new pri_queue*/
pri_queue_t *PriQueueCreate(compare_func_t cmp_func, void *param)
{
	pri_queue_t *new_pq = NULL;
	
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

	assert(pri_queue);
	SortedListInsert(pri_queue->list, data);
	
	return 1;


}

/* pop item from the front of the pri_queue*/
void PriQueueDequeue(pri_queue_t *pri_queue)
{
	
	assert(pri_queue && !PriQueueIsEmpty(pri_queue));

	SortedListRemove(SortedListIterPrev(SortedListEnd(pri_queue->list)));
	

}

/*get value of the front item of the pri_queue*/
void *PriQueuePeek(const pri_queue_t *pri_queue)
{ 
	assert(pri_queue && !PriQueueIsEmpty(pri_queue));
	
	return SortedListIterGetData(SortedListIterPrev(SortedListEnd(pri_queue->list)));

}
/*return the sizeof pri_queue*/
size_t PriQueueSize(const pri_queue_t *pri_queue)
{
	assert(pri_queue);
	
	return SortedListSize(pri_queue->list);

}

/*check if pri_queue is empty*/
int PriQueueIsEmpty(const pri_queue_t *pri_queue)	/* return value empty - 1, not empty - 0 */
{

	return (SortedListIterIsEqual(SortedListBegin(pri_queue->list), SortedListEnd(pri_queue->list)));

}


/*remove all elements*/
void PriQueueClear(pri_queue_t *pri_queue)
{
	assert(pri_queue);
	
	/* freeing all queue elements */
	while (!PriQueueIsEmpty(pri_queue))
	{
		PriQueueDequeue(pri_queue);
	}
}


/*remove elements with a certain UID*/
void PriQueueErase(pri_queue_t *pri_queue, is_match_t is_match_func, void *param)
{

	assert(pri_queue && !PriQueueIsEmpty(pri_queue));
	
	SortedListRemove(SortedListFindIf(SortedListBegin(pri_queue->list), SortedListEnd(pri_queue->list), is_match_func, param));
	
	

}

