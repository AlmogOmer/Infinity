#include "priority_queue.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define UNUSED(x) (void)(x)
static void Test(void);

typedef struct 
{
    int id_num;
    int u_id;
    char name[50];
}person_t;

static int is_match_func(const void* data1,const void* data2, const void* param)
{
	int u_id1, u_id2;
	UNUSED(param);
    u_id1 = ((person_t *)data1)->u_id;
	u_id2 = ((person_t *)data2)->u_id;

   return u_id1 == u_id2;
}


static int IsBefore(const void *new_elem, const void *curr_elem, const void *param)
{
	int newP, currP;
	newP = ((person_t*)new_elem)->id_num;
	currP = ((person_t*)curr_elem)->id_num;

	if (*(int*)param == 1)
	{
		return (newP < currP);
	}
	else
	{
		return (newP > currP);
	}
}

int main(void)
{
	Test();
	
	return 0;
}

static void Test(void)
{
	person_t i1, i2, i3;
	pri_queue_t *pq;
	
	int param = 1;
	int param_u_id1 = 11;
	int param_u_id2 = 22;
	int param_u_id3 = 33;
	
	i1.id_num = 1;
	i1.u_id = 11;
	
	i2.id_num = 2;
	i2.u_id = 22;
	
	i3.id_num = 3;
	i3.u_id = 33;
	
	
	pq = PriQueueCreate(IsBefore, &param);

	
	assert(0 == PriQueueSize(pq));
	assert(1 == PriQueueIsEmpty(pq));
	
	assert(0 == PriQueueEnqueue(pq, &i2));
	assert(0 == PriQueueEnqueue(pq, &i3));
	assert(0 == PriQueueEnqueue(pq, &i1));
	
	assert(0 == PriQueueIsEmpty(pq));
	
	PriQueueDequeue(pq);
	/*assert(&i2 ==  PriQueuePeek(pq));*/
	printf("%d\n",*(int *)PriQueuePeek(pq));

	PriQueueDequeue(pq);
	PriQueueDequeue(pq);
	
	assert(0 == PriQueueSize(pq));
	
	assert(0 == PriQueueEnqueue(pq, &i3));
	assert(0 == PriQueueEnqueue(pq, &i2));
	assert(0 == PriQueueEnqueue(pq, &i1));
	
	PriQueueErase(pq, &param_u_id1, is_match_func, NULL);
	PriQueueErase(pq, &param_u_id2, is_match_func, NULL);
	PriQueueErase(pq, &param_u_id3, is_match_func, NULL);
	
	PriQueueDequeue(pq);
	assert(0 == PriQueueSize(pq));

	PriQueueDestroy(pq);

	puts("SUCCESS");
}



