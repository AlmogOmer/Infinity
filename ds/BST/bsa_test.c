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
    bst_iter_t iter1, iter2, iter3, iter4, from, to;
    int a = 20;
    int b = 10;
    int c = 30;
    int d = 15;
    int e = 5;
    int f = 7;
    int g = 12;
    int h = 35;
    int i = 25;
    int j = 40;
    int x = 0;
    
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
    if (!(*(int*)BstIterGetData(BstBegin(bst))== 10))
    {
        printf("failed in getdata\n");
    }
    BstInsert(bst, &c);

    iter2 = BstFind(bst, &c);
	
	if(!(*(int*)BstIterGetData(iter2) == 30))
	{
		printf("failed in getdata\n");
	}

    if (!(*(int*)BstIterGetData(BstIterPrev(BstEnd(bst)))== 30))
    {
        printf("failed in getdata\n");
    }
    
    if ( 3 != BstSize(bst))
    {
        printf("failed in size\n");
    }
    /*printf("end is %d\n",*(int *)BstIterGetData(BstIterPrev(BstEnd(bst))));
    from = BstBegin(bst);
    printf("from is %d\n",*(int *)BstIterGetData(from));
    from = BstIterNext(from);
    printf("from is %d\n",*(int *)BstIterGetData(from));
    from = BstIterNext(from);
    printf("from is %d\n",*(int *)BstIterGetData(from));
    
    /*to = BstEnd(bst);
    
   /* while(!BstIterIsEqual(from, to))
    {
        x = *(int *)BstIterGetData(from);
        printf("%d ",x);
        from = BstIterNext(from);
    }*/




    
    BstForEach(BstBegin(bst), BstEnd(bst), print, NULL);






    BstDestroy(bst);
    return 0;
}










