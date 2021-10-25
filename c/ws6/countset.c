#include <stdio.h>
int CountSetLoop(int x);
int main()
{
	int x = 56;
	printf("%d", CountSetLoop(x));
	return 0;

}


int CountSetLoop(int x)
{
	int counter = 0;
	unsigned int mask = 1;
	
	while (0 != mask)
	{
		if (0 != (x & mask))
		{
			counter++;
		}
		
		mask <<= 1;
	}
	return counter;
}
