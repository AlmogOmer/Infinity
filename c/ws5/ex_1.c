#include <stdio.h>
typedef void (*func)(int);
void Print (int x);
struct print_me {
		int x;
		func pf;
		};
int main()
{
	
	int i = 0;
	struct print_me arr[10];
	for (i=0; i<10; ++i)
	{
		arr[i].x = i;
		arr[i].pf = Print;
		arr[i].pf(arr[i].x);
	}
	return 0;
}

void Print(int x)
{
	printf("%d",x);
}
