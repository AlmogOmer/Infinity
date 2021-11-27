#include "variable_alloc.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{

	void *pool = NULL;
	var_alloc_t *vsa = NULL;
	void *data1 = NULL;
	void *data2 = NULL;
	void *data3 = NULL;
	void *data4 = NULL;
	size_t pool_size = 300;

	pool = malloc(pool_size);
	if(NULL == pool)
	{
	exit(1);
	}

	vsa = VSAInit(pool,pool_size);

	
	printf("Lgest Memory is: %lu\n", LargestChunkAvailable(vsa));


	if (276 != LargestChunkAvailable(vsa))
	{
		puts("Fail 1");
	}	
	data1 = VSAAlloc(vsa, 22);

	printf("Lgest Memory now is: %lu\n", LargestChunkAvailable(vsa));
	if (236 != LargestChunkAvailable(vsa))
	{
		puts("Fail 2");
	}

	VSAFree(data1);
	
	if (276 != LargestChunkAvailable(vsa))
	{
		puts("Fail 3");
	}
	
	data1 = VSAAlloc(vsa, 15);
	
	if (244 != LargestChunkAvailable(vsa))
	{
		puts("Fail 4");
	}
	data2 = VSAAlloc(vsa, 1118); /* Not Enough memory  */
	if (244 != LargestChunkAvailable(vsa))
	{
		puts("Fail 5");
	}
	if (NULL != data2)
	{
		puts("Fail 6");
	}
	data3 = VSAAlloc(vsa, 45);
	if (180 != LargestChunkAvailable(vsa))
	{
		puts("Fail 7");
	}
	data2 = VSAAlloc(vsa, 13);
	if (148 != LargestChunkAvailable(vsa))
	{
		puts("Fail 8");
	}
	
	data4 = VSAAlloc(vsa, 6);
	
	if (124 != LargestChunkAvailable(vsa))
	{
		puts("Fail 9");
	}
	VSAAlloc(vsa, 80);
	VSAFree(data4);
	VSAFree(data3);
	VSAFree(data2);

	data2 = VSAAlloc(vsa, 40);
	if (76 != LargestChunkAvailable(vsa))
	{
		puts("Fail 10");
	}
	

	free(pool);

	puts("SUCCESS");



	
    return 0;
}
