#include <stdio.h>
#include <stdlib.h>
int main()
{
	int a[10]={0};
	int *b = (int*)malloc(10);
	printf("%d", a[11]);
	a[11] = 2;
	if (*b > 0)
	{
		printf("yes");
	}
	free(b);
	return 0;
}
	
