#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "singly_list.h"


typedef struct 
{
    size_t idNum;
} person_t;


static int is_match_func(const void* data, void* param)
{
    person_t* p = (person_t*)data;

    if (p->idNum == *(size_t*)param)
    {
        return 1;
    }

    return 0;
}

static int print(void* data, void* param)
{

	(void)param;
	printf("%lu\n", *(size_t*)data);
	return 1;
}

int main() 
{

    slist_t *list = SListCreate();
    slist_t* list2 = SListCreate();
	
    
	slist_iter_t iter = SListBegin(list);
	slist_iter_t iter2 = SListBegin(list);
	slist_iter_t iter3 = SListBegin(list2);
	
	int a = 5;
	char b [15] = "abc";
	int c = 100;
	size_t test1;
	person_t p1, p2, p3;
    	slist_iter_t iter4, iter5, iter6;
	
	
	if(!(SListIterIsEqual(iter, iter2) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
		
	
    	if(!(SListCount(list) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	SListInsert(iter, &a);
	
	if(!(SListCount(list) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(*(int*)SListIterGetData(iter) == 5))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	SListInsert(iter, b); /*a, b */
	
	
	if(!(SListCount(list) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}
	

	if(!(strcmp((char*)SListIterGetData(iter),"abc" ) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	SListInsert(iter, &c);/*a, c, b*/
	
	if(!(SListCount(list) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}
	

	if(!(*(int*)SListIterGetData(iter) == 100))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	SListRemove(iter);/*a, b*/
	
	if(!(SListCount(list) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}

	SListDestroy(list);
	
	/***********************************************************/
	
	p1.idNum = 111;
	p2.idNum = 445;
	p3.idNum = 123;
	
	SListInsert(iter3, &p1);
    	SListInsert(iter3, &p2);
    	SListInsert(iter3, &p3);
    	
    	if(!(SListCount(list2) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}
    	
	iter4 = SListBegin(list2);
	iter5 = SListEnd(list2);
	
	
	if(!(SListIterIsEqual(iter4, iter5) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	test1 = 445;
	
	iter6 = SListFind(SListBegin(list2), SListEnd(list2), is_match_func, &test1);
	
	if(!(((person_t*)SListIterGetData(iter6))->idNum == 445))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	SListForEach(SListBegin(list2), SListEnd(list2), print, NULL);
	
	SListDestroy(list2);
	
   return 0;
}
