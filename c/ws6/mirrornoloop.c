#include <stdio.h>
unsigned int ByteMirrornoLoop(unsigned char x);
int main()
{
	unsigned char x = 137;
	printf("%u", ByteMirrornoLoop(x));	
	return 0;
}



unsigned int ByteMirrornoLoop(unsigned char x)
{
	x = ((x & 0xF0) >> 4) | ((x & 0xF) << 4);
	x = ((x & 0xCC) >> 2) | ((x & 0x33) << 2);
	x = ((x & 0xAA) >> 1) | ((x & 0x55) << 1);
	
	return x;
}
