#include "fixed_aloc.h"
#include <stddef.h>
#include <stdio.h>
#include <assert.h>

struct Node{
        node_t *next;
};

struct FixedAlloc{
	
	node_t *head;
};

static size_t ModifiedBlockSize(size_t block_size)
{
	assert(block_size > 0);
	
	if (0 != block_size % sizeof(size_t))	/* aligning block to word boundry */
	{
		block_size += sizeof(size_t) - block_size % sizeof(size_t);
	}
	
	return (block_size);
}

fixed_alloc_t* FSAllocInit(void* pool, size_t pool_size, size_t block_size)
{
	
	node_t *temp = NULL;
	assert(pool && num_blocks > 0 && block_size > 0);
	
	fixed_alloc_t *new_alloc = pool;
	
	 
	new_alloc->head = (node_t *)((size_t)new_alloc + sizeof(new_alloc)) ;
	temp = new_alloc->head;
	
	block_size = ModifiedBlockSize(block_size);
	while ((size_t)temp < (size_t)pool + pool_size - block_size)
	{
		
		temp->next = (node_t *)((size_t)temp + block_size);
		
		temp = temp->next;
	}
	
	temp->next = NULL;
	
	return new_alloc;
}

/* return address for a block */
void* FSAllocAlloc(fixed_alloc_t* alloc)
{
	void *ptr = NULL;
	assert(alloc);
	
	if (alloc->head)
	{
		ptr = alloc->head;
		alloc->head = alloc->head->next;
		
	}
	
	return ptr;

}


/* free the specific block */
void FSAllocFree(fixed_alloc_t* alloc, void* block)
{
	node_t *temp = NULL;
	assert(alloc && block);
	
	temp = block;
	temp -> next = alloc->head;
	alloc->head = temp;


}


size_t FSAllocCountFree(fixed_alloc_t* alloc)
{
	node_t *temp = NULL;
	size_t counter = 0;
	
	assert(alloc);
	temp = alloc->head;
	while (temp)
	{
		temp = temp->next;
		++counter;
	}
	
	return counter;

}


size_t FSAllocSuggestSize(size_t num_blocks, size_t block_size)
{
	assert(num_blocks > 0 && block_size > 0);
	
	block_size = ModifiedBlockSize(block_size);

	return (sizeof(fixed_alloc_t) + block_size * num_blocks);
}





   
