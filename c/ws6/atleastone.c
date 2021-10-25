#include <stdio.h>
int atleastone(unsigned char x);
int main()
{
	unsigned char x = 68;
	printf("%d", atleastone(x));
	return 0;
}


int atleastone(unsigned char x)
{
	return (((x >> 2) | (x >> 6)) & 1);
}
