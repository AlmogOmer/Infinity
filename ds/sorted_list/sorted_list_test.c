#include <assert.h>
#include <stdio.h>
#include "sorted_list.h"


static int IsBefore(const void *new_elem, const void *curr_elem, void *param)
{
	(void)param;
	return ((*(int *) new_elem) < (*(int *) curr_elem));
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
static void MergeTest(void);



int main()
{
	
	CreateTest();
	IterTest();
	InsertTest();
	FindEachTest();
	/*MergeTest();*/

	return 0;
}

static void CreateTest(void)
{
	sorted_list_t *list = SortedListCreate(IsBefore, NULL);
	assert(list);
	
	assert(0 == SortedListSize(list));
	
	SortedListDestroy(list);
	
	puts("SUCCESS- Create Test");
}

static void IterTest(void)
{
	sorted_list_iter_t begin_iter = NULL;
	sorted_list_iter_t end_iter = NULL;
	
	sorted_list_t *list = SortedListCreate(IsBefore, NULL);
	assert(list);
	
	begin_iter = SortedListBegin(list);
	end_iter = SortedListEnd(list);
	
	assert(begin_iter == end_iter);
	
	assert(1 == SortedListIterIsEqual(begin_iter, end_iter));
	
	SortedListDestroy(list);
	
	puts("SUCCESS- Iterator Test");
}

static void InsertTest(void)
{
	int i1 = 45;
	int i2 = 23;
	int i3 = 36;
	int i4 = 58;
	
	sorted_list_iter_t iter = NULL;
	
	sorted_list_t *list = SortedListCreate(IsBefore, NULL);
	
	assert(NULL != SortedListInsert(list, &i1));
	assert(NULL != SortedListInsert(list, &i2));
	assert(NULL != SortedListInsert(list, &i3));
	assert(NULL != SortedListInsert(list, &i4));
	
	iter = SortedListBegin(list);
	assert(1 == SortedListIterIsEqual(iter, SortedListBegin(list)));
	assert((*(int *) SortedListIterGetData(iter)) == i2);
	iter = SortedListNext(iter);
	assert((*(int *) SortedListIterGetData(iter)) == i3);
	iter = SortedListNext(iter);
	assert((*(int *) SortedListIterGetData(iter)) == i1);
	iter = SortedListNext(iter);
	assert((*(int *) SortedListIterGetData(iter)) == i4);
	iter = SortedListNext(iter);
	assert(1 == SortedListIterIsEqual(iter, SortedListEnd(list)));
	
	iter = SortedListRemove(SortedListNext(SortedListBegin(list)));
	assert((*(int *) SortedListIterGetData(iter)) == i1);
	
	iter = SortedListBegin(list);
	assert(1 == SortedListIterIsEqual(iter, SortedListBegin(list)));
	assert((*(int *) SortedListIterGetData(iter)) == i2);
	iter = SortedListNext(iter);
	assert((*(int *) SortedListIterGetData(iter)) == i1);
	iter = SortedListNext(iter);
	assert((*(int *) SortedListIterGetData(iter)) == i4);
	iter = SortedListNext(iter);
	assert(1 == SortedListIterIsEqual(iter, SortedListEnd(list)));
	
	iter = SortedListRemove(SortedListBegin(list));
	assert((*(int *) SortedListIterGetData(iter)) == i1);
	
	iter = SortedListBegin(list);
	assert(1 == SortedListIterIsEqual(iter, SortedListBegin(list)));
	assert((*(int *) SortedListIterGetData(iter)) == i1);
	iter = SortedListNext(iter);
	assert((*(int *) SortedListIterGetData(iter)) == i4);
	iter = SortedListNext(iter);
	assert(1 == SortedListIterIsEqual(iter, SortedListEnd(list)));
	
	SortedListDestroy(list);
	
	puts("SUCCESS- Insert Test");
}

/*
static void FindEachTest(void)
{
	int i1 = 45;
	int i2 = 23;
	int i3 = 36;
	int i4 = 58;
	
	int i = 0;
	
	sorted_list_t *list = SortedListCreate(IsBefore, NULL);
	assert(list);
	
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
/*
static void MergeTest(void)
{
	int i1 = 45;
	int i2 = 23;
	int i3 = 36;
	int i4 = 58;
	
	int i = 0;
	
	sorted_list_t *list1 = SortedListCreate(IsBefore, NULL);
	sorted_list_t *list2 = SortedListCreate(IsBefore, NULL);
	assert(list1 && list2);
	
	assert(NULL != SortedListInsert(list2, &i2));
	assert(NULL != SortedListInsert(list2, &i3));
	assert(NULL != SortedListInsert(list1, &i1));
	assert(NULL != SortedListInsert(list1, &i4));
	
	SortedListMerge(list1, list2);
	
	assert(1 == SortedListForEach(SortedListBegin(list1), SortedListEnd(list1), PrintList, &i));
	assert(0 == strcmp(buffer, "23,36,45,58,"));
	
	assert(1 == SortedListIsEmpty(list2));
	assert(0 == SortedListSize(list2));
	
	assert(0 == SortedListIsEmpty(list1));
	assert(4 == SortedListSize(list1));
	
	SortedListMerge(list1, list2);
	
	i = 0;
	assert(1 == SortedListForEach(SortedListBegin(list1), SortedListEnd(list1), PrintList, &i));
	assert(0 == strcmp(buffer, "23,36,45,58,"));
	
	assert(1 == SortedListIsEmpty(list2));
	assert(0 == SortedListSize(list2));
	
	assert(0 == SortedListIsEmpty(list1));
	assert(4 == SortedListSize(list1));
	
	SortedListMerge(list2, list1);
	
	i = 0;
	assert(1 == SortedListForEach(SortedListBegin(list2), SortedListEnd(list2), PrintList, &i));
	assert(0 == strcmp(buffer, "23,36,45,58,"));
	
	assert(1 == SortedListIsEmpty(list1));
	assert(0 == SortedListSize(list1));
	
	assert(0 == SortedListIsEmpty(list2));
	assert(4 == SortedListSize(list2));

	SortedListDestroy(list1);
	SortedListDestroy(list2);
	
	puts("SUCCESS - Merge Test");
}*/

