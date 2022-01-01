#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__
#include"common_types.h"
#include <stdlib.h>

typedef struct Pri_Queue pri_queue_t;

/*creat new pri_queue*/
extern pri_queue_t *PriQueueCreate(cmp_func_t cmp_func,  void *param);

/*destroy pri_queue*/
extern void PriQueueDestroy(pri_queue_t *pri_queue);

/* insert new item to back of the pri_queue */
extern int PriQueueEnqueue(pri_queue_t *pri_queue, const void *data); 

/* pop item from the front of the pri_queue*/
extern void PriQueueDequeue(pri_queue_t *pri_queue); 

/*get value of the front item of the pri_queue*/
extern void *PriQueuePeek(const pri_queue_t *pri_queue); 

/*return the sizeof pri_queue*/
extern size_t PriQueueSize(const pri_queue_t *pri_queue);

/*check if pri_queue is empty*/
extern int PriQueueIsEmpty(const pri_queue_t *pri_queue);	/* return value empty - 1, not empty - 0 */

/*remove all elements*/
extern void PriQueueClear(pri_queue_t *pri_queue);

/*remove elements with a certain UID*/
extern void PriQueueErase(pri_queue_t *pri_queue, const void *data ,match_func_t is_match_func, void *param);

#endif
