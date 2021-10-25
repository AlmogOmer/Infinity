#include <stdio.h>
long pow2 (unsigned int x, unsigned int y);
int main()
{
	unsigned int x = 4;
	unsigned int y = 3;
	pow2(x,y);
	return 0;
}

long pow2 (unsigned int x, unsigned int y)
{
	long result = x<<y;
	printf("%lu", result);
	return result;
} 
