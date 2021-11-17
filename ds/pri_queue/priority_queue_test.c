#include "priority_queue.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

static void Test(void);

static int IsBefore(const void *data1, const void *data2, void *param);
static int IsEqual(const void *val, void *param);

int main(void)
{
	Test();
	
	return 0;
}

static void Test(void)
{
	int i1 = 1;
	int i2 = 2;
	int i3 = 3;
	
	pq_t *pq = PriQueueCreate(IsBefore, NULL);
	
	assert(pq);
	
	assert(0 == PriQueueSize(pq));
	assert(1 == PriQueueIsEmpty(pq));
	
	assert(0 == PriQueueEnqueue(pq, &i2));
	assert(0 == PriQueueEnqueue(pq, &i3));
	assert(0 == PriQueueEnqueue(pq, &i1));
	
	assert(0 == PriQueueIsEmpty(pq));
	
	assert(i1 == *(int *) PriQueueDequeue(pq));
	assert(i2 == *(int *) PriQueuePeek(pq));

	assert(i2 == *(int *) PriQueueDequeue(pq));
	assert(i3 == *(int *) PriQueueDequeue(pq));
	
	assert(0 == PriQueueSize(pq));
	
	assert(0 == PriQueueEnqueue(pq, &i3));
	assert(0 == PriQueueEnqueue(pq, &i2));
	assert(0 == PriQueueEnqueue(pq, &i1));
	
	assert(i2 == *(int *) PriQueueErase(pq, IsEqual, &i2));
	assert(i3 == *(int *) PriQueueErase(pq, IsEqual, &i3));
	assert(i1 == *(int *) PriQueueErase(pq, IsEqual, &i1));
	
	assert(0 == PriQueueSize(pq));
	
	PriQueueDestroy(pq);

	puts("SUCCESS");
}

/* comperator to sort list by increasing values */
static int IsBefore(const void *data1, const void *data2, void *param)
{
	(void)param;
	
	return ((*(int *) data1) < (*(int *) data2));
}

static int IsEqual(const void *val, void *param)
{	
	return (*(int *) val == *(int *) param);
}

