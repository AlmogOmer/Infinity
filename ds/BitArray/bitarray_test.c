
#include <stdio.h>
#include <assert.h>
#include<string.h>
#include "bit_array.h"
int main()
{
	size_t idx = 2;
	size_t steps = 2;
	bitstate_t value = 1;
	bitarray_t array = 5;
	char dest[64] ={0};
	bitarray_t ba = 5425425414641;

	
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
	assert(0==strcmp(BitArrayToString(ba, dest), "1001110111100110100100011011111100111110001"));
	assert(7==BitArrayToggleBit(array, idx));
	return 0;
}
