#include <stdio.h>
#include <string.h>
extern size_t size;
void test_memmove(void);
void *MeMcpy(void *dest,void *src ,size_t n);
void *MeMmove(void *dest,void *src ,size_t n);


void test_memmove(void)
{
	int result1 = 0;
	int result2 = 0;
	int result3 = 0;
	int result4 = 0;
	char arr[50] = {0};
	strncpy(arr, "abcdefghijklmnopqrstuvwxyz1234567890", 50);
	result1 = strcmp(memmove(arr, arr+8, 15), MeMmove(arr, arr+8, 15));/* Memcpy call */
	printf("%d\n", result1);
	result2 = strcmp(memmove(arr+8, arr, 16),MeMmove(arr+8, arr, 16)) ;/* aligned, n % 8 == 0 */
	printf("%d\n", result2);
	result3 = strcmp(memmove(arr+8, arr, 14),MeMmove(arr+8, arr, 14)) ;/* aligned, n % 8 != 0 */
	printf("%d\n", result3);
	result4 = strcmp(memmove(arr+8, arr, 6),MeMmove(arr+8, arr, 6)) ;	/* n < 8 */	
	printf("%d\n", result4);
}

void *MeMmove(void *dest,void *src ,size_t n)
{
	size_t n1 = 0;
	size_t n2 = 0;
	size_t n3 = 0;
	size_t i = 0;
	if ((size_t)src < (size_t)dest)
	{
		if((size_t)src % size)
		{
			n1 = size - (size_t)src%size;
			for (i=0; i<n1; ++i)
			{
				*((char *)dest+n-1-i)= *((char *)src+n-1-i);
			}
			
		}
		
		n -= n1;
		n2 = n/size;
		for (i=0; i<n2; ++i)
		{
			*((size_t *)dest + (char)n1 +n-1-i) =  *((size_t *)src + (char)n1 +n-1-i); 
		}
		
		n3 = n - (n2*size);
		for (i=0; i<n3; ++i)
		{
			*((char *)dest +(char)n1 +n2 + n-1-(char)i)=*((char *)src +(char)n1 + n2+ n-1-(char)i);
		}
		
	}
		
	else
		dest = MeMcpy(dest,src ,n);
	
	return dest;

}



