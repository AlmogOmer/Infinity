#include <stdio.h>
void swap (int *x, int *y);
int main ()
{
	int x = 0, y = 0;
	printf("enter x: ");
	scanf("%d", &x);
	printf("enter y: ");
	scanf("%d", &y);
	swap(&x, &y);
	printf("x value is: %d\n y value is:%d",x, y);
	return 0;
}

void swap (int *x, int *y)
{
	int temp = 0;
	temp = *y;
	*y = *x; 
	*x = temp; 
}
	
	
