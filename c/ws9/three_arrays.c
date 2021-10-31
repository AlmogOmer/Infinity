#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
int result [256] = {0};
void Three_Arr(char *arr1, int len1, char *arr2, int len2, char *arr3, int len3);
void test(void);
int main()
{

	test();
	return 0;
}

void test(void)
{
	char arr1[] = {'a', 'b', 'c', 'e', 'g', 'y', 't', 'i', 'z'};
	char arr2[] = {'a', 'b', 'c', 'f', 'g', 'z', 't', 'i', 'z', 'z', 'z', 'u', 'p'};
	char arr3[] = {'q', 'b', 'd', 'f', 'h','z', 's', 'o'};
	
	int len1 = sizeof(arr1) / sizeof(arr1[0]);
	int len2 = sizeof(arr2) / sizeof(arr2[0]);
	int len3 = sizeof(arr3) / sizeof(arr3[0]);
	
	Three_Arr(arr1, len1, arr2, len2, arr3, len3);
	
	
}

void Three_Arr(char *arr1, int len1, char *arr2, int len2, char *arr3, int len3)
{
	
	int i = 0;
	
	for (i = 0; i < len3; ++i)					/* loop on arr3 */
	{
		result[(int)arr3[i]] = -1;
	}
	
	for (i = 0; i < len1; ++i)					/* loop on arr1 */
	{
		if (0 == result[(int)arr1[i]])		/* char is not in arr3 */
		{
			result[(int)arr1[i]] = 1;
		}
	
	}
	
	for (i = 0; i < len2; ++i)					/* loop on arr2 */
	{
		if (1 == result[(int)arr2[i]])		/* char is in arr1 */
		{
			result[(int)arr2[i]] = 2;
		}
	
	}

	for (i = 0; i < 256; ++i)			/* print the desired chars */
	{
		if (2 == result[i])
		{
			printf("%c\n", i);
						
		}
	}
}
