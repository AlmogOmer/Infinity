#include <stdio.h>
int BothOn(unsigned char x);
int main()
{
	unsigned char x = 68;
	printf("%d", BothOn(x));
	return 0;
}


int BothOn(unsigned char x)
{
	return ((x >> 2) & (x >> 6) & 1);
}
