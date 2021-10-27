#include<stdio.h>
#define MAX_2(X,Y) ((X>Y)?(X):(Y))
#define MAX_3(X,Y,Z) ((X>Y)?((X>Z)?X:Z):((Y>Z)?Y:Z))
int main()
{
	int x = 1;
	int y = 2;
	int z = 3;
	printf("%d\n%d\n", MAX_2(x,y), MAX_3(x,y,z));
	return 0;
}
