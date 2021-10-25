#include<stdio.h>
void PrintFloat(void);
int main()
{
	PrintFloat();
	return 0;
}


void PrintFloat(void)
{
	float f = 352.5485;
	float *fp = &f;
	unsigned int *ip = (unsigned int *)fp;
	unsigned int x = *ip;
	int i = 0;
	
	
	for (i = 0; i<32 ; ++i)
	{
		int bit = x & 0x80000000;     /*2 powered by 31*/
		if (bit)
		{
			printf("%d", 1);
		}
		else 
		{
			printf("%d", 0);
		}
		x <<= 1;

	}
	
}
