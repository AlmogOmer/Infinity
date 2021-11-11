#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "circular_buffer.h"
#include <unistd.h>
#include <stdio.h>

int main()
{
	int x = 165, z = 200, w = 500;
	int *y = (int*)malloc(sizeof(int));
	cbuffer_t *cbuffer = CBufferCreate(10);
	assert(CBufferIsEmpty(cbuffer) == 1);
	assert(CBufferCapacity(cbuffer) == 10);
	assert(CBufferFreeSpace(cbuffer) == 10);
	
	CBufferWrite(cbuffer, &x, 4);
	CBufferWrite(cbuffer, &z, 4);
	CBufferRead(cbuffer, y, 4);
	CBufferWrite(cbuffer, &w, 4);
	assert(CBufferFreeSpace(cbuffer) == 2);
	assert(CBufferIsEmpty(cbuffer) == 0);
	
	CBufferRead(cbuffer, y, 4);
	CBufferRead(cbuffer, y, 4);
	
	assert(CBufferIsEmpty(cbuffer) == 1);
	
	free(y);
	CBufferDestroy(cbuffer);
	
	return 0;
}

