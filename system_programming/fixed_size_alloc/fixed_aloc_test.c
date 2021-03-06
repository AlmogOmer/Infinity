#include "fixed_aloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>	
#include <string.h>	

int main()
{

	const size_t SIZE = 104;
	const size_t BLOCK_SIZE = 16;
	const size_t SIZE_STRUCT = 8;

	size_t init_free_blocks = (SIZE - SIZE_STRUCT)/ BLOCK_SIZE;
	
	void *pool = NULL;
	fixed_alloc_t *fsa = NULL;
	
	char *test1 = NULL;
	char *test2 = NULL;
	char *test3 = NULL;
	char *test4 = NULL;
	char *test5 = NULL;
	char *test6 = NULL;
	char *test7 = NULL;
	
	pool = malloc(SIZE);
	if(!pool)
	{
		fprintf(stderr, "MEMORY ERROR");
		exit(1);
	}
	
	if(!(FSAllocSuggestSize(init_free_blocks,BLOCK_SIZE) == SIZE))
	{
		printf("fail in %d\n", __LINE__);
		
	}
	
	fsa = FSAllocInit(pool, SIZE, BLOCK_SIZE);
	
	if(!(FSAllocCountFree(fsa) == init_free_blocks))
	{
		printf("fail in %d\n", __LINE__);
		
	}
	
	test1 = FSAllocAlloc(fsa);
	strcpy(test1, "Dumbeldore");
	
	if(!(strcmp(test1, "Dumbeldore") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	FSAllocFree(fsa, test1);
	test7 = FSAllocAlloc(fsa);
	strcpy(test7, "woww");		
	test2 = FSAllocAlloc(fsa);
	
	strcpy(test2, "Harry Potter");
	
	if(!(strcmp(test2, "Harry Potter") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(FSAllocCountFree(fsa) == init_free_blocks - 2))
	{
		printf("fail in %d\n", __LINE__);
		
	}
	
	FSAllocFree(fsa, test2);
	
	if(!(FSAllocCountFree(fsa) == init_free_blocks - 1))
	{
		printf("fail in %d\n", __LINE__);
		
	}
	
	test3 = FSAllocAlloc(fsa);
	strcpy(test3, "Harry Potter");	
	test4 = FSAllocAlloc(fsa);
	strcpy(test4, "Muhammad Def");		
	test5 = FSAllocAlloc(fsa);
	strcpy(test5, "Alibaba");	
	test6 = FSAllocAlloc(fsa);	
	strcpy(test6, "Voldemort");
	test1 = FSAllocAlloc(fsa);
	strcpy(test1, "Dumbeldore");
	
	if(!(FSAllocCountFree(fsa) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	free(pool);
	return 0;
	

}
