#include <stdio.h>
#include <stdlib.h>
double *copy(double array[], int n);
int main ()
{
	int n = 0;
	printf("enter the number of elements: ");
	scanf("%d", &n);
	double array [n];
	double *array_copy = NULL;
	printf("enter the array's elements: ");
	int i = 0;
	for (i=0; i<n; ++i)
	{
		scanf("%lf", &array[i]);
	}
	array_copy = copy(array,n);
	printf("the copied array: ");
	for (i=0; i<n; ++i)
	{
		printf("\n%.2f", array_copy[i]);
	}
	return 0;
}

double *copy(double array[], int n)
{
	double *cpy = malloc(sizeof(int)*n);
	int i = 0;
	for (i=0;i<n;++i)
	{
		cpy[i] = array[i];
	}
	return cpy;
}
