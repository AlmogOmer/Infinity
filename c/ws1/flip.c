#include <stdio.h>
int flip(int num);
int main() 
{
	int num = 0;
	printf ("enter a number:");
	scanf ("%d", &num);
	printf ("%d", flip(num));
	return 0;
}

int flip(int num) 
{
	int flipped_num = 0;
	while (num != 0) 
	{
		flipped_num = (flipped_num * 10) + (num % 10);
		num /= 10;
	}
	return flipped_num;
}
