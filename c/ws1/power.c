#include <stdio.h>
double power(int n);
int main()
{
	int n; 
	printf("enter your n:");
	scanf ("%d", &n); 
	printf("%.2lf",power (n));
	return 0;
}

double power(int n)
{
	double result = 1;
	int v_to_pow = 10;
	int i;
	if (n < 0)
	{
		n = -n;
		v_to_pow = 1/v_to_pow;
	}
	for (i = 1; i <= n; ++i)
	{
		result = v_to_pow * result; 
	}
	return result; 
}
	
