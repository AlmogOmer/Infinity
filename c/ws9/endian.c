#include <stdlib.h>
#include <stdio.h>

#define IS_LIT_END(x) (*(char *)&x == x)

int IsLitEnd(void);

int main()
{
	int x = 1;
	printf("%d\n", IsLitEnd());
	
	printf("%d\n", IS_LIT_END(x));
	
	return 0;
}

int IsLitEnd(void)
{
	int n = 1;
	char c = *(char *) &n;
	if(c == 1)
		return 1;
	else
		return 0;
}

