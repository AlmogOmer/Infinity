#include <stdio.h>
#include <assert.h>
#include<string.h>
#include "bit_array.h"

static void RevStr(char *str);

bitarray_t BitArraySetAll()
{
	return (0xffffffffffffffff); 
}

bitarray_t BitArrayResetAll()
{
	return (bitarray_t)0;
}

bitarray_t BitArraySetOn(bitarray_t array, size_t idx)
{
	assert (idx <= 63);
	return (array | ((bitarray_t)1<<(idx-1)));
}

bitarray_t BitArraySetOff(bitarray_t array, size_t idx)
{
	assert (idx <= 63);
	if (array & ((bitarray_t)1<<(idx-1)))
	{
		return (array ^ ((bitarray_t)1<<(idx-1)));
	}
	return array; 
}

bitarray_t BitArraySetBit(bitarray_t array, size_t idx, bitstate_t value)
{
	assert (idx <= 63);
	if (value)
	{
		return (array | ((bitarray_t)1<<(idx-1)));
	}
	
	return (array ^ ((bitarray_t)1<<(idx-1)));
}

size_t BitArrayGetValue(bitarray_t array, size_t idx)
{
	assert (idx <= 63);
	return ((array>>(idx-1)) & 1);
}

bitarray_t BitArrayFlip(bitarray_t array)
{
	return ~array;
}

bitarray_t BitArrayMirror(bitarray_t array)
{
	array =((array & 0xFFFFFFFF00000000) >> 32) | ((array & 0x00000000FFFFFFFF) << 32); 
	array =((array & 0xFFFF0000FFFF0000) >> 16) | ((array & 0x0000FFFF0000FFFF) << 16);
	array =((array & 0xFF00FF00FF00FF00) >> 8) | ((array & 0x00FF00FF00FF00FF) << 8);
	array =((array & 0xF0F0F0F0F0F0F0F0) >> 4) | ((array & 0x0F0F0F0F0F0F0F0F) << 4);
	array =((array & 0xCCCCCCCCCCCCCCCC) >> 2) | ((array & 0x3333333333333333) << 2); 
	array =((array & 0xAAAAAAAAAAAAAAAA) >> 1) | ((array & 0x5555555555555555) << 1); 

    return array;
}

size_t BitArrayCountOn(bitarray_t array)
{
	size_t counter = 0;		
	while (array)
	{
		++counter;
		array &= array-1;
		
	}
	
	return counter;
}

size_t BitArrayCountOff(bitarray_t array)
{
	return BitArrayCountOn(~array);
}

bitarray_t BitArrayRotR(bitarray_t array, size_t steps)
{
	return (array<<(64-steps) | array>>steps);
}

bitarray_t BitArrayRotL(bitarray_t array, size_t steps)
{
	return (array>>(64-steps) | array<<steps);
}


char *BitArrayToString(bitarray_t array, char *dest)
{

	char *temp = dest;
	assert(array);
	while (array)
	{
		if (array & 1)
		{
			*dest = '1';
			++dest;
			array >>= 1;
		}
		else
		{
			*dest = '0';
			++dest;
			array >>= 1;
		}
	}
	*(dest+1) = '\0';
	RevStr(temp);
	return temp;

}

bitarray_t BitArrayToggleBit(bitarray_t array, size_t idx)
{
	assert (idx <= 63);
	return BitArraySetBit(array, idx, ~BitArrayGetValue(array, idx));

}


static void RevStr(char *str)
{
	int i = 0, len = 0, temp = 0;
	while (str[len])
  	{
		++len;
	}
	for (i = 0; i < len/2; ++i)
	{
		temp = str[i];  
        	str[i] = str[len - i - 1];  
        	str[len - i - 1] = temp;  
	}  
}



















