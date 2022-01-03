#include "heap.h"
#include "dynamic_vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>	
#include<time.h>
#define UNUSED(x) (void)(x)

static void Test(void);
static void test1();
static void test2();

int main(void)
{
	Test();
    /*test1();*/
	test2();
	return 0;
}

static int MaxInt(const void *data1, const void *data2, const void *param)
{
	UNUSED(param);
	return (*(int *) data1 - *(int *) data2);
}

static int IntIsEqual(const void *data1, const void *data2, const void *param)
{
	UNUSED(param);
	return data1 == data2;
}

static void Test(void)
{
	int arr[10] = {0};
	size_t i = 0;
	heap_t *heap = HeapCreate(MaxInt, NULL);
	assert(heap);
	assert(0 == HeapSize(heap));
	assert(HeapIsEmpty(heap));

	for (i = 0; i < 10; i++)
	{
		arr[i] = i + 1;
		assert(0 == HeapPush(heap, &arr[i]));
		printf("%d\n", *(int *) HeapPeek(heap));
		assert(i + 1 == HeapSize(heap));
		assert(!HeapIsEmpty(heap));
	}

	printf("after removing 1: %d\n", *(int *) HeapRemove(heap,&arr[0], IntIsEqual, NULL));
	printf("finding 2: %d\n", *(int *)HeapFind(heap, &arr[1], IntIsEqual, NULL));

	printf("peek: %d\n", *(int *) HeapPeek(heap));
    /*printf("size: %lu\n", HeapSize(heap));*/
        /*assert(i+1 == HeapSize(heap));*/
		/*assert(arr[i] == *(int *) HeapPeek(heap));*/
	HeapPop(heap);
    printf("peek: %d\n", *(int *) HeapPeek(heap));
    /*printf("size: %lu\n", HeapSize(heap));*/
    
    HeapPop(heap);
	printf("peek: %d\n", *(int *) HeapPeek(heap));
    /*printf("size: %lu\n", HeapSize(heap));*/
    
    HeapPop(heap);
    printf("peek: %d\n", *(int *) HeapPeek(heap));
    /*printf("size: %lu\n", HeapSize(heap));*/

    HeapPop(heap);
    printf("peek: %d\n", *(int *) HeapPeek(heap));
    /*printf("size: %lu\n", HeapSize(heap));*/

    HeapPop(heap);
    printf("peek: %d\n", *(int *) HeapPeek(heap));
    /*printf("size: %lu\n", HeapSize(heap));*/

    HeapPop(heap);
    printf("peek: %d\n", *(int *) HeapPeek(heap));
    /*printf("size: %lu\n", HeapSize(heap));*/

    HeapPop(heap);
    printf("peek: %d\n", *(int *) HeapPeek(heap));
    
    HeapPop(heap);
    printf("peek: %d\n", *(int *) HeapPeek(heap));

	HeapDestroy(heap);

	puts("SUCCESS");
}

static void test1()
{
	heap_t *heap = NULL;
	int b[10];
	size_t i;
	srand(0);
	heap = HeapCreate(MaxInt, NULL);

	for (i = 0; i < 10; ++i)
	{
		b[i] = rand();

		HeapPush(heap, &b[i]);
	}

	for (i = 0; i < 10; ++i)
	{
		if (b[i] != *(int *)HeapFind(heap, &b[i], IntIsEqual, NULL))
		{
			printf("fail in %d\n", __LINE__);
		}
	}

	if (b[0] != *(int *)HeapRemove(heap, &b[0], IntIsEqual, NULL))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	HeapDestroy(heap);

}

static void test2()
{
	heap_t *heap = NULL;
	int test1 = 50;
	int test2 = 30;
	int test3 = 0;
	int test4 = 4;
	int test5 = 7;
	int test6 = 9;
	int test7 = 70;
	int test8 = 1;

	heap = HeapCreate(MaxInt, NULL);
	printf("***after push***\n");
	HeapPush(heap, &test1);
	printf("%d\n", *(int *)HeapPeek(heap));
	HeapPush(heap, &test2);
	printf("%d\n", *(int *)HeapPeek(heap));
	HeapPush(heap, &test3);
	printf("%d\n", *(int *)HeapPeek(heap));
	HeapPush(heap, &test4);
	printf("%d\n", *(int *)HeapPeek(heap));
	HeapPush(heap, &test5);
	printf("%d\n", *(int *)HeapPeek(heap));
	HeapPush(heap, &test6);
	printf("%d\n", *(int *)HeapPeek(heap));
	HeapPush(heap, &test7);
	printf("%d\n", *(int *)HeapPeek(heap));
	HeapPush(heap, &test8);
	printf("%d\n", *(int *)HeapPeek(heap));

	if (70 != *(int *)HeapPeek(heap))
	{
		printf("fail in %d\n", __LINE__);
	}
	printf("***after pop***\n");
	HeapPop(heap);
	printf("%d\n", *(int *)HeapPeek(heap));

	HeapPop(heap);
	printf("%d\n", *(int *)HeapPeek(heap));
	
	HeapPop(heap);
	printf("%d\n", *(int *)HeapPeek(heap));
	
	HeapPop(heap);
	printf("%d\n", *(int *)HeapPeek(heap));

	HeapDestroy(heap);
}


