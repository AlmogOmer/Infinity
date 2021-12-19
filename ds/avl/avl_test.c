#include "avl.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define UNUSED(x) (void)(x)

static void Test(void);
static void Test1(void);

int main(void)
{
	Test();
	/*Test1();*/

	return 0;
}


static int CmpInt(const void *data1, const void *data2, const void *param)
{
	int result = *(int *) data1 - *(int *) data2;
	UNUSED(param);
	if (result > 0)
	{
		return 1;
	}
	if (result < 0)
	{
		return -1;
	}

	return 0;
}

static int PrintInt(const void *data, const void *param)
{
	UNUSED(param);

	printf("%d\n", *(int *) data);

	return 1;
}

static void Test(void)
{
	static int arr[8] = {8, 3, 10, 14, 6, 1, 4, 7};
	size_t i = 0;
	avl_t *tree = AvlCreate(CmpInt, NULL);
	assert(tree);
	assert(AvlIsEmpty(tree));
	assert(0 == AvlSize(tree));
/*	assert(0 == AVLTreeHeight(tree));*/

	for (i = 0; i < 8; i++)
	{
		assert(0 == AvlInsert(tree, &arr[i]));
		assert(i + 1 == AvlSize(tree));
		assert(!AvlIsEmpty(tree));
	}

	AvlForEach(tree, PrintInt, NULL, IN_ORDER);
	puts("*****************");
	AvlForEach(tree, PrintInt, NULL, PRE_ORDER);
	puts("*****************");
	AvlForEach(tree, PrintInt, NULL, POST_ORDER);
	
	AvlDestroy(tree);

	puts("*****************");
	puts("SUCCESS");
}



static void Test1(void)
{
	avl_t *tree = AvlCreate(CmpInt, NULL);
	static int arr9[15] = {13, 3, 4, 12, 14, 10, 5, 1, 8, 2, 7, 9, 11, 6, 18};
	size_t i = 0;
	assert(tree);
	assert(AvlIsEmpty(tree));

	for (i = 0; i < 15; i++)
	{
		assert(AvlSize(tree) == i);
		assert(0 == AvlInsert(tree, arr9 + i));
		printf("after %ld insertions, tree height is %ld\n", (i + 1), AvlHeight(tree));
	}

	assert(AvlSize(tree) == 15);

	assert(!AvlIsEmpty(tree));

	assert(1 == AvlForEach(tree, PrintInt, NULL,IN_ORDER));
	puts("*************");

	AvlRemove(tree, &arr9[14]);
	assert(1 == AvlForEach(tree, PrintInt, NULL,IN_ORDER));
	puts("*************");
	AvlRemove(tree, &arr9[3]);
	assert(1 == AvlForEach(tree, PrintInt, NULL,IN_ORDER));
	puts("*************");
	AvlRemove(tree, &arr9[0]);
	assert(1 == AvlForEach(tree, PrintInt, NULL,IN_ORDER));
	puts("*************");

	assert(AvlSize(tree) == (15 - 3));

	AvlDestroy(tree);

	puts("*****************");
	puts("test 1 SUCCESS");
}


