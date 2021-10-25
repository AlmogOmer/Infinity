#include <stdio.h>
unsigned char SwapBits(unsigned char x);
int main()
{
	unsigned char x = 16;
	printf("%d\n",SwapBits(x));
	return 0;
}



unsigned char SwapBits(unsigned char x)
{
	
	unsigned char bit3 = 1 & x>>2;
	unsigned char bit5 = 1 & x>>4;
	unsigned char tmp = (bit3)^(bit5);
	unsigned char add = (tmp<<4)^(tmp<<2);
	return (x ^ add) ;
}
