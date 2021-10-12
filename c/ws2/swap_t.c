#include <stdio.h>
void swap_t (size_t *x, size_t *y);
int main ()
{
	size_t x = sizeof(int);
	size_t y = sizeof(double);
	swap_t(&x, &y);
	printf("x value is: %ld\n y value is:%ld",x, y);
	return 0;
}

void swap_t (size_t *x, size_t *y)
{
	int temp = 0;
	temp = *y;
	*y = *x; 
	*x = temp; 
}
	
