#include <stdio.h>
unsigned int ByteMirrorLoop(unsigned char x);
int main()
{
	unsigned char x = 137;
	printf("%u", ByteMirrorLoop(x));	
	return 0;
}



unsigned int ByteMirrorLoop(unsigned char x)
{
	unsigned int result = 0;
	int i = 0;
	
	for (i = 0 ; i < 8 ; ++i )       /* 8 bits in a byte */
	{
		result >>= 1;
		result |= 128 & x; /*2 powered by 7*/
		x <<= 1;
	}
	
	return result;
}



