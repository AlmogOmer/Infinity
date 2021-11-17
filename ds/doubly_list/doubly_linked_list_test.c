#include <stdlib.h>
#include "doubly_linked_list.h"
#include <assert.h>
#include <stdio.h>

void TestSplice1();
void TestSplice2();
void TestSplice3();
void TestSplice4();
void TestSplice5();
void TestSplice6();
void TestSplice7();
void TestSplice8();
void TestSpliceAll();

int PrintAll (void *data, void *param)
{
	if(NULL == data || NULL == param)
	{
		return 0;
	}
	printf("%d ", *(int*)data);
	return 1;
}


void DListPrint(dlist_t *list)
{
	int x = 3;
	action_func_t print = PrintAll;
	printf("List Elements:          ");
	DListForEach(DListBegin(list), DListEnd(list), print, &x);
	printf("\n");
}



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
		
	

	TestSpliceAll();
	
		
	
	return 0;
}



void TestSpliceAll()
{
	TestSplice1();
	TestSplice2();
	/*TestSplice3();*/
	/*TestSplice4();*/
	/*TestSplice5();*/
	/*TestSplice6();*/
	/*TestSplice7();*/
	/*TestSplice8();*/
}



void TestSplice1()
{
	dlist_iter_t iter;
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
	dlist_t *list = DListCreate();
	iter = DListBegin(list);
	DListInsert(iter, &a);
	DListInsert(iter, &b);		
	DListInsert(iter, &c);	
	DListInsert(iter, &d);
	DListInsert(iter, &e);
	DListInsert(iter, &f);
	
	puts("Splice test 1");
	puts("before:");
	DListPrint(list);
	puts("after:");
	DListSplice(DListIterNext(DListBegin(list)), DListIterNext(DListIterNext(DListBegin(list))), DListIterPrev(DListEnd(list)));	
	DListPrint(list);

	puts("###");
# if 0
# endif
	DListDestroy(list);
}


void TestSplice2()
{
	dlist_iter_t iter;
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
	dlist_t *list = DListCreate();
	iter = DListBegin(list);
	DListInsert(iter, &a);
	DListInsert(iter, &b);		
	DListInsert(iter, &c);	
	DListInsert(iter, &d);
	DListInsert(iter, &e);
	DListInsert(iter, &f);
	
	puts("Splice test 2");
	puts("before:");
	DListPrint(list);
	puts("after:");
	DListSplice(DListEnd(list), DListIterNext(DListBegin(list)), DListIterPrev(DListIterPrev(DListEnd(list))));
	DListPrint(list);
	puts(" ###");

# if 0
# endif
	DListDestroy(list);
}

void TestSplice3()
{
	dlist_iter_t iter;
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
	dlist_t *list = DListCreate();
	iter = DListBegin(list);
	DListInsert(iter, &a);
	DListInsert(iter, &b);		
	DListInsert(iter, &c);	
	DListInsert(iter, &d);
	DListInsert(iter, &e);
	DListInsert(iter, &f);

	puts("Splice test 3");
	puts("before:");
	DListPrint(list);
	puts("after:");
	DListSplice(DListBegin(list), DListIterNext(DListBegin(list)), DListIterPrev(DListIterPrev(DListEnd(list))));
	DListPrint(list);

	puts("###");
# if 0
# endif
	DListDestroy(list);
}



void TestSplice4()
{
	dlist_iter_t iter;
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
	dlist_t *list = DListCreate();
	iter = DListBegin(list);
	DListInsert(iter, &a);
	DListInsert(iter, &b);		
	DListInsert(iter, &c);	
	DListInsert(iter, &d);
	DListInsert(iter, &e);
	DListInsert(iter, &f);
	
	puts("Splice test 4");
	puts("before:");
	DListPrint(list);
	puts("after:");
	DListSplice(DListBegin(list), DListIterNext(DListBegin(list)), DListIterPrev(DListEnd(list)));
	DListPrint(list);
	puts("###");
# if 0
# endif
	DListDestroy(list);
}


void TestSplice5()
{
	dlist_iter_t iter;
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
	dlist_t *list = DListCreate();
	iter = DListBegin(list);
	DListInsert(iter, &a);
	DListInsert(iter, &b);		
	DListInsert(iter, &c);	
	DListInsert(iter, &d);
	DListInsert(iter, &e);
	DListInsert(iter, &f);

	puts("Splice test 5");
	puts("before:");
	DListPrint(list);
	puts("after:");
	
	DListSplice(DListBegin(list), DListIterNext(DListIterNext(DListBegin(list))), DListIterPrev(DListEnd(list)));
	DListPrint(list);
	puts("###");
# if 0
# endif
	DListDestroy(list);
}



void TestSplice6()
{
	dlist_iter_t iter;
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
	dlist_t *list = DListCreate();
	iter = DListBegin(list);
	DListInsert(iter, &a);
	DListInsert(iter, &b);		
	DListInsert(iter, &c);	
	DListInsert(iter, &d);
	DListInsert(iter, &e);
	DListInsert(iter, &f);
	
	puts("Splice test 6");
	puts("before:");
	DListPrint(list);
	puts("after:");
	
	DListSplice(DListEnd(list), DListBegin(list), DListIterPrev(DListIterPrev(DListEnd(list))));
	DListPrint(list);
	puts("###");
# if 0
# endif
	DListDestroy(list);
}


void TestSplice7()
{
	dlist_iter_t iter;
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
	dlist_t *list = DListCreate();
	iter = DListBegin(list);
	DListInsert(iter, &a);
	DListInsert(iter, &b);		
	DListInsert(iter, &c);	
	DListInsert(iter, &d);
	DListInsert(iter, &e);
	DListInsert(iter, &f);
	
	puts("Splice test 7");
	puts("before:");
	DListPrint(list);
	puts("after:");
	
	DListSplice(DListEnd(list), DListBegin(list), DListIterPrev(DListIterPrev(DListIterPrev(DListEnd(list)))));
	DListPrint(list);
	puts("###");
# if 0
# endif
	DListDestroy(list);
}


void TestSplice8()
{
	dlist_iter_t iter;
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
	dlist_t *list = DListCreate();
	iter = DListBegin(list);
	DListInsert(iter, &a);
	DListInsert(iter, &b);		
	DListInsert(iter, &c);	
	DListInsert(iter, &d);
	DListInsert(iter, &e);
	DListInsert(iter, &f);
	
	puts("Splice test 8");
	puts("before:");
	DListPrint(list);
	puts("after:");
	
	DListSplice(DListEnd(list), DListBegin(list), DListIterPrev(DListEnd(list)));
	DListPrint(list);
	puts("###");
# if 0
# endif
	DListDestroy(list);
}








