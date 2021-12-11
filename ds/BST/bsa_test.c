#include "bsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>



static int cmp_func(const void *new_elem, const void *curr_elem, const void *param)
{
    int diff = (*(int *) new_elem - *(int *) curr_elem);

    UNUSED(param);

    if (diff > 0)
    {
        return 1;
    }
    if (diff < 0)
    {
        return -1;
    }
    return 0;
	
}

static int print(void* data, const void* param)
{

	UNUSED(param);
	printf("%d\n", *(int*)data);
	return 1;
}



int main()
{
    bst_iter_t iter1, iter2, iter3, iter4, from;
    int a = 8;
    int b = 10;
    int c = 3;
    int d = 6;
    int e = 1;
    int f = 7;
    int g = 4;
    int h = 14;
   
    
    bst_t *bst = BstCreate(cmp_func, NULL);
    if (0 == BstIsEmpty(bst))
    {
        printf("failed in isempty\n");
    }
    if ( 0 == BstIterIsEqual(BstBegin(bst), BstEnd(bst)))
    {
        printf("failed in isequal\n");
    }
    if ( 0 != BstSize(bst))
    {
        printf("failed in size\n");
    }
    BstInsert(bst, &a);
    if (1 == BstIsEmpty(bst))
    {
        printf("failed in insert\n");
    }
    if ( 1 == BstIterIsEqual(BstBegin(bst), BstEnd(bst)))
    {
        printf("failed in isequal\n");
    }
    BstInsert(bst, &b);
    if (!(*(int*)BstIterGetData(BstBegin(bst))== 8))
    {
        printf("failed in getdata begin\n");
    }
    
    iter1 = BstFind(bst, &b);
	
	if(!(*(int*)BstIterGetData(iter1) == 10))
	{
		printf("failed in getdata iter 1\n");
	}

    
    BstInsert(bst, &c);

    iter2 = BstFind(bst, &c);
	
	if(!(*(int*)BstIterGetData(iter2) == 3))
	{
		printf("failed in getdata iter 2\n");
	}

    if (!(*(int*)BstIterGetData(BstIterPrev(BstEnd(bst)))== 10))
    {
        printf("failed in getdata of end\n");
    }
    
    if ( 3 != BstSize(bst))
    {
        printf("failed in size after 3 insertions\n");
    }
    
    BstInsert(bst, &d);
    BstInsert(bst, &e);
    BstInsert(bst, &f);
    BstInsert(bst, &g);
    BstInsert(bst, &h);

    if (0 != BstIsEmpty(bst))
    {
        printf("failed in isempty after insertions\n");
    }
    iter3 = BstFind(bst, &f);
	
	if(!(*(int*)BstIterGetData(iter3) == 7))
	{
		printf("failed in getdata iter 3\n");
	}

    if (!(*(int*)BstIterGetData(BstIterPrev(BstEnd(bst)))== 14))
    {
        printf("failed in getdata end\n");
    }
    
    if ( 8 != BstSize(bst))
    {
        printf("failed in size after all insertions\n");
    }

    iter4 = BstFind(bst, &g);
    if(!(*(int*)BstIterGetData(iter4) == 4))
	{
		printf("failed in getdata iter 4\n");
	}

    from = BstIterPrev(BstEnd(bst));
    from = BstIterPrev(from);
    if(!(*(int*)BstIterGetData(from) == 10))
	{
		printf("failed in getdata from iter\n");
	}

    printf("tree before removing: \n");
    BstForEach(BstBegin(bst), BstEnd(bst), print, NULL);
    
    BstRemove(from);
    printf("tree after removing 10: \n");
    BstForEach(BstBegin(bst), BstEnd(bst), print, NULL);

    from = BstBegin(bst);
    from = BstIterNext(from);
    BstRemove(from);
    printf("tree after removing 3: \n");
    BstForEach(BstBegin(bst), BstEnd(bst), print, NULL);
    
    from = BstBegin(bst);
    BstRemove(from);
    printf("tree after removing 1: \n");
    BstForEach(BstBegin(bst), BstEnd(bst), print, NULL);

    from = BstIterPrev(BstEnd(bst));
    BstRemove(from);
    printf("tree after removing 14: \n");
    BstForEach(BstBegin(bst), BstEnd(bst), print, NULL);

    BstDestroy(bst);
    return 0;
}










