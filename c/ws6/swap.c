#include<stdio.h>
void Swap(int *x, int *y);
int main()
{
	int ix = 4;
	int iy = 5;
	int *x = &ix;
	int *y = &iy;
	Swap(x, y);
	printf("%d %d", ix, iy); 
	return 0;

}


void Swap(int *x, int *y)
{
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
}
