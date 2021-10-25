#include <stdio.h>
int ispow2 (unsigned int n);
int ispow2_no_loop (unsigned int n);
int main()
{
	unsigned int n = 4;
	printf("%d\n",ispow2(n));
	printf("%d\n",ispow2_no_loop(n));
	return 0;
}

int ispow2 (unsigned int n)
{
	unsigned int temp = 0;
	unsigned int i = 0; 
	
	for (i = 0; temp < n ; ++i)
	{
		temp = 1<<i;
		if (temp == n)
			return 1;
	}
	return 0;
} 

int ispow2_no_loop (unsigned int n)
{
	if ((n&(n-1)) == 0)
		return 1;
	return 0;
} 
