#include <stdio.h>
#include <string.h>
size_t size = 8;
void test_memset(void);
void *MeMset(void *arr, int c, size_t n);
void test_memcpy(void);
void *MeMcpy(void *dest,void *src ,size_t n);
void test_memmove(void);
void *MeMmove(void *dest,void *src ,size_t n);
int main()
{
	test_memset();
	test_memcpy();
	test_memmove();
	return 0;
}
