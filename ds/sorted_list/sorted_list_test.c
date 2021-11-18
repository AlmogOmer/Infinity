#include <assert.h>
#include <stdio.h>
#include "sorted_list.h"

typedef struct 
{
    int id_num;
    int u_id;
    char name[50];
}person_t;


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

static int is_match_func(void* data, void* param)
{
    int u_id;
    u_id = ((person_t *)data)->u_id;

   return u_id == *(int*)param;
}

static int print(void* data, void* param)
{

	(void)param;
	printf("%d\n", *(int*)data);
	return 1;
}

static void CreateTest(void);
static void IterTest(void);
static void InsertTest(void);
static void FindEachTest(void);
static void FindIfTest(void);
static void MergeTest(void);



int main()
{
	
	CreateTest();
	IterTest();
	InsertTest();
	FindEachTest();
	FindIfTest();
	MergeTest();

	return 0;
}

static void CreateTest(void)
{
	int param = 1;
	sorted_list_t *list = SortedListCreate(IsBefore, &param);
	
	assert(0 == SortedListSize(list));
	
	SortedListDestroy(list);
	
	puts("SUCCESS- Create Test");
}

static void IterTest(void)
{
	int param = 1;
	
	sorted_list_t *list = SortedListCreate(IsBefore, &param);
	assert(list);

	
	assert(1 == SortedListIterIsEqual(SortedListBegin(list), SortedListEnd(list)));
	
	SortedListDestroy(list);
	
	puts("SUCCESS- Iterator Test");
}

static void InsertTest(void)
{
	int param = 1;
	int i1 = 45;
	int i2 = 23;
	int i3 = 36;
	int i4 = 58;
	sorted_list_iter_t iter;
	
	sorted_list_t *list = SortedListCreate(IsBefore, &param);
	
	assert(NULL != SortedListInsert(list, &i1));
	assert(NULL != SortedListInsert(list, &i2));
	assert(NULL != SortedListInsert(list, &i3));
	assert(NULL != SortedListInsert(list, &i4));
	
	iter = SortedListBegin(list);
	assert(1 == SortedListIterIsEqual(iter, SortedListBegin(list)));
	assert((*(int *) SortedListIterGetData(iter)) == i2);
	iter = SortedListIterNext(iter);
	assert((*(int *) SortedListIterGetData(iter)) == i3);
	iter = SortedListIterNext(iter);
	assert((*(int *) SortedListIterGetData(iter)) == i1);
	iter = SortedListIterNext(iter);
	assert((*(int *) SortedListIterGetData(iter)) == i4);
	iter = SortedListIterNext(iter);
	assert(1 == SortedListIterIsEqual(iter, SortedListEnd(list)));
	
	SortedListRemove(SortedListIterNext(SortedListBegin(list)));
	iter = SortedListBegin(list);
	assert(1 == SortedListIterIsEqual(iter, SortedListBegin(list)));
	assert((*(int *) SortedListIterGetData(iter)) == i2);
	iter = SortedListIterNext(iter);
	assert((*(int *) SortedListIterGetData(iter)) == i1);
	iter = SortedListIterNext(iter);
	assert((*(int *) SortedListIterGetData(iter)) == i4);
	iter = SortedListIterNext(iter);
	assert(1 == SortedListIterIsEqual(iter, SortedListEnd(list)));
	
	SortedListRemove(SortedListBegin(list));
	
	iter = SortedListBegin(list);
	assert(1 == SortedListIterIsEqual(iter, SortedListBegin(list)));
	assert((*(int *) SortedListIterGetData(iter)) == i1);
	iter = SortedListIterNext(iter);
	assert((*(int *) SortedListIterGetData(iter)) == i4);
	iter = SortedListIterNext(iter);
	assert(1 == SortedListIterIsEqual(iter, SortedListEnd(list)));
	
	SortedListDestroy(list);
	
	puts("SUCCESS- Insert Test");
}


static void FindEachTest(void)
{

	int param = 1;
	int i1 = 45;
	int i2 = 23;
	int i3 = 36;
	int i4 = 58;
	int i = 0;

	
	sorted_list_t *list = SortedListCreate(IsBefore, &param);
	
	assert(NULL != SortedListInsert(list, &i1));
	assert(NULL != SortedListInsert(list, &i2));
	assert(NULL != SortedListInsert(list, &i3));
	assert(NULL != SortedListInsert(list, &i4));
	
	assert(i1 == *(int *) SortedListIterGetData(SortedListFind(SortedListBegin(list), SortedListEnd(list),&i1)));
	assert(i2 == *(int *) SortedListIterGetData(SortedListFind(SortedListBegin(list), SortedListEnd(list),&i2)));
	assert(i3 == *(int *) SortedListIterGetData(SortedListFind(SortedListBegin(list), SortedListEnd(list),&i3)));
	assert(i4 == *(int *) SortedListIterGetData(SortedListFind(SortedListBegin(list), SortedListEnd(list),&i4)));

	assert(1 == SortedListForEach(SortedListBegin(list), SortedListEnd(list), print, &i));


	SortedListDestroy(list);
	
	puts("SUCCESS - Find + ForEach Test");
}

static void FindIfTest(void)
{
	sorted_list_t *list;
	person_t i1, i2, i3;
	int param = 1;
	int param_u_id = 33;
	
	i1.id_num = 1;
	i1.u_id = 11;
	
	i2.id_num = 2;
	i2.u_id = 22;
	
	i3.id_num = 3;
	i3.u_id = 33;
	
	list = SortedListCreate(IsBefore, &param);
	assert(NULL != SortedListInsert(list, &i1));
	assert(NULL != SortedListInsert(list, &i2));
	assert(NULL != SortedListInsert(list, &i3));
	
	assert(&i3 ==  SortedListIterGetData(SortedListFindIf(SortedListBegin(list), SortedListEnd(list),is_match_func, &param_u_id)));

	SortedListDestroy(list);
	
	puts("SUCCESS - FindIf Test");

}
static void MergeTest(void)
{
	int param = 1;
	int i1 = 45;
	int i2 = 23;
	int i3 = 36;
	int i4 = 58;
	
	int i = 0;
	
	sorted_list_t *list1 = SortedListCreate(IsBefore, &param);
	sorted_list_t *list2 = SortedListCreate(IsBefore, &param);
	
	assert(NULL != SortedListInsert(list2, &i2));
	assert(NULL != SortedListInsert(list2, &i3));
	
	assert(NULL != SortedListInsert(list1, &i1));
	assert(NULL != SortedListInsert(list1, &i4));
	
	SortedListForEach(SortedListBegin(list1), SortedListEnd(list1), print, &i);
	SortedListForEach(SortedListBegin(list2), SortedListEnd(list2), print, &i);
	
	SortListMerge(list1, list2);
	
	assert(1 == SortedListForEach(SortedListBegin(list1), SortedListEnd(list1), print, &i));
	
	assert(4 == SortedListSize(list1));
	
	
	SortedListDestroy(list1);
	
	puts("SUCCESS - Merge Test");
}

