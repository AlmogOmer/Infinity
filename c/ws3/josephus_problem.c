#include <stdio.h>
#include <stdlib.h>

int Yosef(int n);

int main()
{
	int n = 4592740;
	
	printf("%d\n", Yosef(n));
	
	return 0;
}

int Yosef(int n)
{
	int i = 0;			/* running index from 0 to n-1 */
	int kill = 0;
	int ptk = n - 1;	/* people to kill (n-1) */
	
	int *circle = (int *) malloc(n * sizeof(n)); /* array with size n */
	if (NULL == circle)
	{
		return -1;		/* allocation failure indication */
	}
	
	while (i < n)		/* all people alive*/
	{
		*(circle + i) = 1; /* like circle[i]*/
		++i;
	}
	i = 0;
	
	while (ptk > 0)
	{	
		if (1 == *(circle + (i % n)))
		{
			if (1 == kill)
			{
				*(circle + (i % n)) = 0;
				--ptk;
				kill = 0;
			}
			else
			{
				kill = 1;
			}
		}
		++i;
	}	
	
	i = 0;
	
	while (1 != *circle)
	{
		++circle;
		++i;
	}
	
	free(circle - i);
	
	return (i + 1);
}


