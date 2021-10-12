#include <stdio.h>
void swap_pointers (size_t **px, size_t **py);
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
	size_t *temp = NULL;
	temp = *py;
	*py = *px; 
	*px = temp; 
}
	
