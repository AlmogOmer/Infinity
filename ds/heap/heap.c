#include "heap.h"
#include "dynamic_vector.h"
#include <stdio.h>
#include<stdlib.h>
#include <assert.h>	

#define PARENT_INDX(i) (((i) - 1)/ 2)
#define LEFT_CHILD_INDX(i) ((2 * (i)) + 1)
#define RIGHT_CHILD_INDX(i) ((2 * (i)) + 2)
#define HAS_PARENT(i) ((i) > 0)

static void PtrSwap(void **x, void **y);
static void HeapifyUp(heap_t *heap, size_t index);
static void HeapifyDown(heap_t *heap, size_t index);


struct Heap
{
	Vector_t *dynvec;
	cmp_func_t cmp_func;
	const void *param;
};

static void PtrSwap(void **x, void **y)
{
	void *tmp = *x;
	*x = *y;
	*y = tmp;
}

static void HeapifyUp(heap_t *heap, size_t index)
{
	void **data1_ptr = (void **) VectorGetAccessToElement(heap->dynvec, index);
	void **data2_ptr = (void **) VectorGetAccessToElement(heap->dynvec, PARENT_INDX(index));

	if (HAS_PARENT(index) && (heap->cmp_func(*data1_ptr, *data2_ptr, heap->param) > 0))
	{
		PtrSwap(data1_ptr, data2_ptr);
		HeapifyUp(heap, PARENT_INDX(index));
	}
}

static void HeapifyDown(heap_t *heap, size_t index)
{
	size_t left_index = LEFT_CHILD_INDX(index);
	size_t right_index = RIGHT_CHILD_INDX(index);
	size_t largest_index = index;

	if (left_index <= HeapSize(heap)-1 &&
	(heap->cmp_func(VectorGetAccessToElement(heap->dynvec, left_index), VectorGetAccessToElement(heap->dynvec, index), heap->param) >= 0))
	{
		largest_index = left_index;
	}

	if (right_index <= HeapSize(heap)-1 &&
	(heap->cmp_func(VectorGetAccessToElement(heap->dynvec, right_index), VectorGetAccessToElement(heap->dynvec, largest_index), heap->param) >= 0))
	{
		largest_index = right_index;
	}

	if (largest_index != index)
	{
		PtrSwap(VectorGetAccessToElement(heap->dynvec, largest_index), VectorGetAccessToElement(heap->dynvec, index));
		HeapifyDown(heap, largest_index);
	}
}



heap_t *HeapCreate(cmp_func_t compare, const void *param)
{
    heap_t *heap = NULL;

	heap = (heap_t *) malloc(sizeof(heap_t));
	if (!heap)
    {
        exit(1);
    }
    
    heap->cmp_func = compare;
    heap->param = param;
    heap->dynvec = VectorCreate(1, sizeof(void *));
    if (!heap->dynvec)
    {
        free(heap);
        heap = NULL;
    }

	return heap;
}

void HeapDestroy(heap_t *heap)
{
	assert(heap);

	VectorDestroy(heap->dynvec);
	free(heap);
}

/* returns 0 if success, 1 if failed*/
int HeapPush(heap_t *heap, const void *data)
{
    size_t size_before, size_after;
    assert(heap);
    
    size_before = HeapSize(heap);
	
    VectorPushBack(heap->dynvec, &data);

	size_after = HeapSize(heap);
    
    HeapifyUp(heap, HeapSize(heap)-1);

	return (size_after == size_before);
}

void HeapPop(heap_t *heap)
{
	
	if (HeapIsEmpty(heap))
    {
        return;
    }

	assert(heap);

	/* swap the root and the last index */
	PtrSwap(VectorGetAccessToElement(heap->dynvec, 0), VectorGetAccessToElement(heap->dynvec, HeapSize(heap)-1));

	/* pop the root */
	VectorPopBack(heap->dynvec);
    
	if (0 < HeapSize(heap))
	{
		HeapifyDown(heap, 0);
	}

}

void *HeapPeek(heap_t *heap)
{
    return *(void **)VectorGetAccessToElement(heap->dynvec, 0);
}

/* 1 if empty, 0 if not*/
int HeapIsEmpty(const heap_t *heap)
{
    assert(heap);
	return (0 == VectorSize(heap->dynvec));
}

size_t HeapSize(const heap_t *heap)
{
    assert(heap);
	return (VectorSize(heap->dynvec));
}

void *HeapRemove(heap_t *heap, const void *data, match_func_t is_match, void *param)
{
	size_t i;
    assert(heap);
    for (i = 0; i < HeapSize(heap); ++i)
    {
        if (is_match(*(void **)VectorGetAccessToElement(heap->dynvec, i), data, param))
        {
            PtrSwap(VectorGetAccessToElement(heap->dynvec, i),
                                VectorGetAccessToElement(heap->dynvec, HeapSize(heap) - 1));
            VectorPopBack(heap->dynvec);
            if (HeapSize(heap) > 0)
            {
                HeapifyDown(heap, i);
            }
            return (void *)data;
        }
    }
    return NULL;
}


void *HeapFind(const heap_t *heap, const void *data, match_func_t is_match, void *param)
{
    size_t i;
    for (i = 0; i < HeapSize(heap); ++i)
    {
        if (is_match(*(void **)VectorGetAccessToElement(heap->dynvec, i), data, param))
        {
            return *(void **)VectorGetAccessToElement(heap->dynvec, i);
        }
    } 
	return NULL;
}


