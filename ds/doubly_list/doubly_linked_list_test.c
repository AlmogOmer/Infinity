#include <stdlib.h>
#include "doubly_linked_list.h"
#include <assert.h>
#include <stdio.h>


static int print(void* data, void* param)
{

	(void)param;
	printf("%d\n", *(int*)data);
	return 1;
}



static int is_match_func(void* data, void* param)
{

    if (*(int *)data == *(int*)param)
    {
        return 1;
    }

    return 0;
}

int main()
{
	
	dlist_t *list = DListCreate();

    	
	dlist_iter_t iter = DListBegin(list);
	dlist_iter_t iter2 = DListEnd(list);

	
	int a = 5;
	int b = 7;
	int c = 100;
	int d = 300;
	int e = 400;
	
	if(!(DListIterIsEqual(iter, iter2) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
		
	
    	if(!(DListSize(list) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	DListInsert(iter, &a);
	
	if(!(DListSize(list) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(*(int*)DListIterGetData(iter) == 5))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	DListInsert(iter, &b); 
	
	if(!(DListSize(list) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	if(!(*(int*)DListIterGetData(iter) == 7))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	DListInsert(iter, &c);
	
	if(!(DListSize(list) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}
	

	if(!(*(int*)DListIterGetData(iter) == 100))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	iter2 = DListFind(DListBegin(list), DListEnd(list), is_match_func, &c);
	
	if(!(*(int*)DListIterGetData(iter2) == 100))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	DListRemove(DListBegin(list));
	
	if(!(DListSize(list) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}

	
	DListPushFront(list, &d);
	iter = DListBegin(list);
	
	if(!(DListSize(list) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(*(int*)DListIterGetData(iter) == 300))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	DListPushBack(list, &e);
	
	if(!(DListSize(list) == 4))
	{
		printf("fail in %d\n", __LINE__);
	}
	/*
	if(!(*(int*)DListIterGetData(DListEnd(list)) == 400))
	{
		printf("fail in %d\n", __LINE__);
	}*/
	
	
	DListPopFront(list);
	
	if(!(DListSize(list) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(*(int*)DListIterGetData(DListBegin(list)) == 7))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	DListPopBack(list);
	iter = DListIterPrev(DListEnd(list));
	
	if(!(DListSize(list) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(*(int*)DListIterGetData(iter) == 5))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	DListForEach(DListBegin(list), DListEnd(list), print, NULL);
	
	DListDestroy(list);
	
	return 0;
}


