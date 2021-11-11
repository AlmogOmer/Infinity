#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "circular_buffer.h"
#include <unistd.h>
#include <stdio.h>


struct CBuffer
{
	
	size_t size;
	size_t start;
	size_t end;
	size_t count_written;
	char arr[1];

};





/*int main ()
{
	size_t size, cnt1, i, cnt2;
	cbuffer_t *buffer = NULL;
	char *buf  = NULL;
	
	size = 20;
	cnt1 = 10;
	cnt2 = 5;
	buffer = CBufferCreate(size);
	buf = (char *)malloc(sizeof(char)*10);
	for (i = 0; i <cnt ; ++i)
	{
		buf[i] = (char)i;
	}
	
	assert(20==CBufferFreeSpace(buffer));
	assert(1==CBufferIsEmpty(buffer));
	assert(20==CBufferCapacity(buffer));

	
	assert(10==CBufferWrite(buffer, buf, cnt1));
	assert(10==CBufferFreeSpace(buffer));
	assert(0==CBufferIsEmpty(buffer));
	
	assert(5==CBufferRead(buffer, buf, cnt2));
	assert(15==CBufferFreeSpace(buffer));
	assert(0==CBufferIsEmpty(buffer));
	
	free(buf);
	CBufferDestroy(buffer);
	return 0;
}*/


/*creates new circular buffer*/
cbuffer_t *CBufferCreate(size_t size)
{
	cbuffer_t *new_cbuff = (cbuffer_t *) malloc(sizeof(cbuffer_t) + sizeof(char) * size);
	
	if (NULL == new_cbuff)
	{
		return NULL;
	}

	
	if (NULL == new_cbuff->arr)
	{

		return NULL;
	}
	
	new_cbuff->start = 0;
	new_cbuff->end = 0;
	new_cbuff->count_written= 0;
	new_cbuff->size = size;
	
	return new_cbuff;
}


/*destroys circular buffer*/
void CBufferDestroy(cbuffer_t *cbuffer)
{
	assert(cbuffer);
	
	free(cbuffer);
	cbuffer = NULL;

}

/* write to a file descriptor */
ssize_t CBufferWrite(cbuffer_t *cbuffer, const void *buf, size_t cnt)
{
	
	size_t i = 0;
	assert(cbuffer && buf && cnt);
	
	if (cnt > CBufferFreeSpace(cbuffer))
	{
		cnt = CBufferFreeSpace(cbuffer);
	}
	
	for (i=0; i<cnt ; ++i)
	{
		
		memcpy(cbuffer->arr + cbuffer->end, (char *)buf + i, 1);
		++cbuffer->count_written;
		cbuffer->end = (cbuffer->end + 1) % cbuffer->size;
	}
	
	return (cnt);

}


/* read from a file descriptor*/
ssize_t CBufferRead(cbuffer_t *cbuffer, void *buf, size_t cnt)
{
	size_t i = 0;
	assert(cbuffer && buf && cnt);
	
	if (cnt > cbuffer->count_written)
	{
		cnt = cbuffer->count_written;
	}
	
	for (i=0; i<cnt ; ++i)
	{
		
		memcpy((char *)buf + i, cbuffer->arr + cbuffer->start , 1);
		--cbuffer->count_written;
		cbuffer->start = (cbuffer->start +1) % cbuffer->size;
	}
	
	return (cnt);


}

/*returns the number of free bytes to write */
size_t CBufferFreeSpace(const cbuffer_t *cbuffer)
{
	assert(cbuffer);
	return (cbuffer->size - cbuffer->count_written);

}

/*checks if the circular buffer is empty*/
int CBufferIsEmpty(const cbuffer_t *cbuffer)	/* return value empty 1, not empty 0 */
{
	assert(cbuffer);
	return (!cbuffer->count_written);

}
/*returns buffer size*/
size_t CBufferCapacity(const cbuffer_t *cbuffer)
{
	assert(cbuffer);
	return cbuffer->size;

}
