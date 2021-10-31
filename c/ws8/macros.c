#include<stdio.h>
#define MAX_2(X,Y) ((X>Y)?(X):(Y))
#define MAX_3(X,Y,Z) ((X>Y)?((X>Z)?X:Z):((Y>Z)?Y:Z))
#define SIZEOF_VAR(X) ((char *)(&X+1)-(char *)&X)
#define SIZEOF_TYPE(type) ((size_t)(1+(type*)0))
int main()
{
	int x = 7;
	int y = 2;
	int z = 3;
	int arr[] = {1,2,3,4};
	printf("%d\n%d\n", MAX_2(x,y), MAX_3(x,y,z));
	printf("%ld\n%lu\n", SIZEOF_VAR(arr), SIZEOF_TYPE(int));
	return 0;
}
