#include <stdio.h>
int add1 (unsigned int x, unsigned int y);
int main()
{
	int x = 2;
	int y = 1;
	printf("%d", add1(x,y));	
	
	return 0;
}

int add1 (unsigned int x, unsigned int y)
{
	int carry = 0;
	while (y != 0)
	{
		
		carry = x & y;
		x = x^y;
		y  = carry<<1;
		
	}
	return x;
}
	
