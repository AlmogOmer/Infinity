#include <stdio.h>
#include <string.h>
extern size_t size;
void test_memcpy(void);
void *MeMcpy(void *dest,void *src ,size_t n);


void test_memcpy(void)
{
	int result1 = 0;
	int result2 = 0;
	int result3 = 0;
	int result4 = 0;
	char arr1[25] = {0};
	char arr2[25] = {0};
	char src[] = "blablablablablablablablanlblabla";
	strcpy(arr2, src);
	result1 = strcmp(memcpy(arr1, arr2, 16), MeMcpy(arr1, arr2, 16));/* aligned, n % 8 == 0 */
	printf("%d\n", result1);
	result2 = strcmp(memcpy(arr1, arr2, 14),MeMcpy(arr1, arr2, 14)) ;/* aligned, n % 8 != 0 */
	printf("%d\n", result2);
	result3 = strcmp(memcpy(arr1+1, arr2+1, 16),MeMcpy(arr1+1, arr2+1, 16)) ;/* not aligned */
	printf("%d\n", result3);
	result4 = strcmp(memcpy(arr1, arr2, 6),MeMcpy(arr1, arr2, 6)) ;	/* n < 8 */	
	printf("%d\n", result4);
}

void *MeMcpy(void *dest,void *src ,size_t n)
{
	size_t n1 = 0;
	size_t n2 = 0;
	size_t n3 = 0;
	size_t buffer = (size_t)dest; 
	size_t i = 0;
	
	if(buffer % size)
	{
		n1 = size - buffer%size;
		for (i=0; i<n1; ++i)
		{
			*((char *)dest+i)= *((char *)src+i);
		}
		
	}
	
	n -= n1;
	n2 = n/size;
	for (i=0; i<n2; ++i)
	{
		*((size_t *)dest + (char)n1 + i) =  *((size_t *)src + (char)n1 + i); 
	}
	
	n3 = n - (n2*size);
	for (i=0; i<n3; ++i)
	{
		*((char *)dest +(char)i +(char)n1 +n2)=*((char *)src +(char)i +(char)n1 + n2);
	}
	
	
	return dest;

}
