#include "fixed_aloc.h"
#include <stddef.h>
#include <stdio.h>
#include <assert.h>

struct Node{
        node_t *next;
};

struct FixedAlloc{
	size_t num_free;
	node_t *head;
};

fixed_alloc_t* FSAllocInit(void* pool, size_t pool_size, size_t block_size)
{
	size_t offset;
	node_t *temp = NULL;
	fixed_alloc_t *new_alloc = pool;
	
	new_alloc->num_free =  0 ; 
	new_alloc->head = (node_t *)((size_t)new_alloc + sizeof(new_alloc)) ;
	temp = new_alloc->head;
	
	offset = block_size % sizeof(size_t);
	if(offset)
	{
		block_size += sizeof(size_t)-offset;
	}
	
	
	while ((size_t)temp < (size_t)pool + pool_size - block_size)
	{
		
		temp->next = (node_t *)((size_t)temp + block_size);
		++(new_alloc->num_free);
		temp = temp->next;
	}
	
	return new_alloc;
}

/* return address for a block */
void* FSAllocAlloc(fixed_alloc_t* alloc)
{
	void *ptr = NULL;
	if (alloc->num_free)
	{
		ptr = alloc->head;
		alloc->head = alloc->head->next;
		--alloc->num_free;
	}
	
	return ptr;

}


/* free the specific block */
void FSAllocFree(fixed_alloc_t* alloc, void* block)
{
	node_t *temp = NULL;
	
	temp = block;
	temp -> next = alloc->head;
	alloc->head = temp;
	++alloc->num_free;

}


size_t FSAllocCountFree(fixed_alloc_t* alloc)
{
	return (alloc->num_free);

}
   
