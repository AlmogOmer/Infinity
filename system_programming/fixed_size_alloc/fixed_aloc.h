#ifndef __FIXED_SIZE_ALLOCATOR_H__
#define __FIXED_SIZE_ALLOCATOR_H__

#include <stddef.h>

/* the memory that the client provide */


/* list of memory... */
typedef struct FixedAlloc fixed_alloc_t;
typedef struct Node node_t;
/*extern size_t SuggestSize();*/

/* get the free space in memory */
extern fixed_alloc_t* FSAllocInit(void* pool, size_t pool_size, size_t block_size);

/* return address for a block */
extern void* FSAllocAlloc(fixed_alloc_t* alloc);

/* free the specific block */
extern void FSAllocFree(fixed_alloc_t* alloc, void* block);


size_t FSAllocCountFree(fixed_alloc_t* alloc);




#endif
