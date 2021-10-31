#include <stdio.h>
#include <string.h>
extern size_t size;
void test_memset(void);
void *MeMset(void *arr, int c, size_t n);


void test_memset(void)
{
	char arr[25] = {0};
	int result1 = 0;
	int result2 = 0;
	strcpy(arr, "Hello World!");
	result1 = strcmp(MeMset(arr,'*', 16), memset(arr,'*', 16)); /* aligned, n % 8 == 0 */
	result2 = strcmp(MeMset(arr,'*', 6),memset(arr,'*', 6)) ;	/* n < 8 */
	printf("%d\n", result1);
	printf("%d\n", result2);
}

void *MeMset(void *arr, int c, size_t n)
{
	size_t n1 = 0;
	size_t n2 = 0;
	size_t n3 = 0;
	size_t buffer = (size_t)arr; 
	size_t word = 0;
	size_t i = 0;
	for (i = 0; i<size; ++i)
	{
		word |= (char)c << (i*size);
	}
	
	if(buffer % size)
	{
		n1 = size - buffer%size;
		for (i=0; i<n1; ++i)
		{
			*((char *)arr+i)= (char)c;
		}
		
	}
	
	n -= n1;
	n2 = n/size;
	for (i=0; i<n2; ++i)
	{
		*((size_t *)arr + (char)n1 + i) =  word; 
	}
	
	n3 = n - (n2*size);
	for (i=0; i<n3; ++i)
	{
		*((char *)arr + (char)i + (char)n1 + n2)= (char)c;
	}
	
	
	return arr;

}



