#include <stdio.h>
#include <assert.h>
#include<string.h>
#include "bit_array.h"
/*int main()
{
	size_t idx = 2;
	size_t steps = 2;
	bitstate_t value = 1;
	bitarray_t array = 5;
	char dest[64] ={0};
	
	assert(7==BitArraySetOn(array, idx));
	assert(5==BitArraySetOff(array, idx));
	assert(7==BitArraySetBit(array, idx, value));
	assert(0==BitArrayGetValue(array, idx));
	assert(0xFFFFFFFFFFFFFFFA==BitArrayFlip(array));
	assert(0xA000000000000000==BitArrayMirror(array));
	assert(2==BitArrayCountOn(array));
	assert(62==BitArrayCountOff(array));
	assert(0x4000000000000001==BitArrayRotR(array, steps));
	assert(20==BitArrayRotL(array, steps));
	assert(0==strcmp("0000000000000000000000000000000000000000000000000000000000000101", BitArrayToString(array, dest)));
	assert(7==BitArrayToggleBit(array, idx));
	return 0;
}*/

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
	int i = 0;
	for (i = 63; i>=0 ; --i)
	{
		dest[i] = (char) BitArrayGetValue(array, 64-i) + '0';
		
	}
	dest[64] = '\0';  
		
	return dest;

}

bitarray_t BitArrayToggleBit(bitarray_t array, size_t idx)
{
	assert (idx <= 63);
	return BitArraySetBit(array, idx, ~BitArrayGetValue(array, idx));

}




















