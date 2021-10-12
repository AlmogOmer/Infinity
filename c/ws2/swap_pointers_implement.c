#include <stdio.h>
void swap_pointers (size_t **px, size_t **py);
void swap_t (size_t *x, size_t *y);
int main ()
{
	size_t x = sizeof(int);
	size_t *px = &x;
	size_t y = sizeof(double);
	size_t *py = &y;
	printf("px is: %p\n py is:%p",(void*)px,(void*)py);
	swap_pointers(&px, &py);
	printf("px is: %p\n py is:%p",(void*)px,(void*)py);
	return 0;
}

void swap_pointers (size_t **px, size_t **py)
{
	swap_t((size_t *)(px),(size_t *)(py));
	 
}

void swap_t (size_t *x, size_t *y)
{
	int temp = 0;
	temp = *y;
	*y = *x; 
	*x = temp; 
}	
