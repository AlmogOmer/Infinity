#include<stdio.h>
unsigned int DevidedBy16(unsigned int x);
int main()
{
	unsigned int x = 33;
	printf("%d", DevidedBy16(x));
	return 0;
	
}

unsigned int DevidedBy16(unsigned int x)
{
	return ((x >> 4) << 4); /* >>4 is diviation by 16 without remainder*/
}
