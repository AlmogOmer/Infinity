#include <stdio.h>
void threebits(unsigned int arr[], int n);
int main()
{
	unsigned int arr[] = {5,7,9,8};
	int n = 4;
	threebits(arr,n);	
	
	return 0;
}

void threebits(unsigned int arr[], int n)
{
	int i = 0;
	unsigned int counter = 0;
	unsigned int mask = 1;
	
	for (i = 0 ; i < n ; ++i)
	{
		counter = 0;			/* reinitializing for every arr index */
		mask = 1;
		
		while (0 != mask)
		{
			if (0 != (arr[i] & mask))
			{
				counter++;
			}
			
			if (3 < counter)
			{
				break;
			}
			
			mask <<= 1;
		}
		
		if (3 == counter)
		{
			printf("%d\n", arr[i]);
		}
	}
}

