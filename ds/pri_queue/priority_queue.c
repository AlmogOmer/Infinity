#include "priority_queue.h"
#include "heap.h"
#include "dynamic_vector.h"
#include <stdlib.h>
#include <assert.h>

struct Pri_Queue
{
	heap_t *heap;
};


/*creat new pri_queue*/
pri_queue_t *PriQueueCreate(cmp_func_t cmp_func, void *param)
{
	pri_queue_t *new_pq = NULL;
	
	new_pq = (pri_queue_t *) malloc(sizeof(pri_queue_t));
	if (NULL == new_pq)
	{
		return NULL;
	}
	
	new_pq->heap = HeapCreate(cmp_func, param);
	if (NULL == new_pq->heap)
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
	
	HeapDestroy(pri_queue->heap);
	pri_queue->heap = NULL;
	
	free(pri_queue);

}

/* insert new item to back of the pri_queue */
int PriQueueEnqueue(pri_queue_t *pri_queue, const void *data)
{

	assert(pri_queue);
	
	return HeapPush(pri_queue->heap, data);


}

/* pop item from the front of the pri_queue*/
void PriQueueDequeue(pri_queue_t *pri_queue)
{
	
	assert(pri_queue && !PriQueueIsEmpty(pri_queue));

	HeapPop(pri_queue->heap);
	

}

/*get value of the front item of the pri_queue*/
void *PriQueuePeek(const pri_queue_t *pri_queue)
{ 
	assert(pri_queue && !PriQueueIsEmpty(pri_queue));
	
	return HeapPeek(pri_queue->heap);

}
/*return the sizeof pri_queue*/
size_t PriQueueSize(const pri_queue_t *pri_queue)
{
	assert(pri_queue);
	
	return HeapSize(pri_queue->heap);

}

/*check if pri_queue is empty*/
int PriQueueIsEmpty(const pri_queue_t *pri_queue)	/* return value empty - 1, not empty - 0 */
{

	return (HeapSize(pri_queue->heap)==0);

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
void PriQueueErase(pri_queue_t *pri_queue, const void *data ,match_func_t is_match_func, void *param)
{

	assert(pri_queue && !PriQueueIsEmpty(pri_queue));

	HeapRemove(pri_queue->heap, data, is_match_func, param);
	

}

