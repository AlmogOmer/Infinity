#include "variable_alloc.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct Block block_t;

struct Block{
	
	size_t block_size;
	size_t free_flag;

};

struct VaribleAlloc{
	
	size_t pool_size;
	
};

static int Merge(block_t *block)
{
	block_t *next = NULL;
	
	
	next = (block_t *) ((size_t) block + block->block_size+ sizeof(block_t));
	
	if (next->free_flag == 1)
	{
		
		block->block_size += next->block_size;
		next = NULL;
		return 1;			
	}
	
	return 0;
}




/* get the free space in memory */
var_alloc_t* VSAInit(void *pool, size_t pool_size)
{
	var_alloc_t *vsa = NULL;
	block_t *block = NULL;
	
	assert(pool);
	
	vsa = pool;
	
	if (pool_size <= (sizeof(var_alloc_t) + sizeof(block_t)))
	{
		return NULL;
	}

	if (0 != (size_t)vsa % sizeof(size_t))	
	{
		vsa = (var_alloc_t *)((size_t)vsa+ sizeof(size_t) - (size_t)pool % sizeof(size_t));
	}
	
	
	vsa->pool_size = pool_size - sizeof(var_alloc_t) - sizeof(block_t) ;
	
	block = (block_t *) ((size_t)vsa + sizeof(var_alloc_t));
	block->block_size = vsa->pool_size;
	block->free_flag = 1;
	
	
	return vsa;

}

/* return address for a block */
void* VSAAlloc(var_alloc_t* vsa, size_t block_size)
{
	void *ptr = NULL;
	block_t *block = (block_t *) ((size_t)vsa + sizeof(var_alloc_t));		
	size_t i = sizeof(var_alloc_t);	/* offset of block */
	
	assert(vsa && block_size > 0);

	
	if (0 != block_size % sizeof(size_t))
	{
		block_size += (sizeof(size_t) - block_size % sizeof(size_t));
	}
		
	
	while (i < vsa->pool_size)
	{
		
		if (block->free_flag == 1)
		{
			
			if (block->block_size >= block_size)	/* we can fit */
			{
				
				if (block->block_size > (block_size + sizeof(block_t)))
				{
					block_t *next_block = (block_t *)((size_t)block + block_size + sizeof(block_t));
					
					next_block->block_size = block->block_size - block_size - sizeof(block_t);
					next_block->free_flag = 1;
					
					block->block_size = block_size;
					
					
				}
				ptr = (void *)((size_t)block + sizeof(block_t));
				block->free_flag = 0;
				return ptr;
			}

			if (Merge(block)==1)
			{
				continue;
			}
		}
		
		i = i + block->block_size + sizeof(block_t);
		block = (block_t *) ((size_t) block + block->block_size + sizeof(block_t));
	}
	
	/*if (block->block_size >= block_size+ sizeof(block_t))	/* last block */
	/*{
		
		ptr = block + sizeof(block_t);
		block->free_flag = 0;
	}*/
	
	return ptr;
}





/* free the specific block */
void VSAFree(void* block)
{
	
	block_t *free_block = NULL;
	assert(block);
	
	free_block = (block_t *)((size_t)block - sizeof(block_t));


	free_block->free_flag = 1;
	
}

/* return the largest free block size */
size_t LargestChunkAvailable(var_alloc_t* vsa)
{
	size_t max_size = 0;
	block_t *block = (block_t *) ((size_t)vsa + sizeof(var_alloc_t));
	size_t i = sizeof(var_alloc_t);
	
	while (i < vsa->pool_size)
	{
		
		if (block->free_flag == 1)
		{
			
			if (Merge(block)==1)
			{
				continue;
			}
		
			max_size = MAX(max_size, block->block_size);
			
		}
		
		i = i + block->block_size + sizeof(block_t);
		block = (block_t *) ((size_t) block + block->block_size+ sizeof(block_t));
	}
	
	max_size = MAX(max_size, block->block_size); /*last block*/
	return max_size;
}







