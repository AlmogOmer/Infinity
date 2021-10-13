#include <stdio.h>
#include <assert.h>
char *StrnCpy(char *dest, const char *src, size_t n);
int main()
{
	char dest[10] = {0};
	printf("dest is now: %s\n", StrnCpy(dest, "hello", 3));
	return 0;	
}

char *StrnCpy(char *dest, const char *src, size_t n)
{
	char *dest_ptr = dest ;
	assert(dest && src);
	while (('\0' != *src) && n)
	{
		*dest = *src;
		++dest;
		++src;
		--n;
	}
	
	while (n)
	{
		*dest = '\0';
		++dest;
		--n;
	}
	
	return dest_ptr;
}
