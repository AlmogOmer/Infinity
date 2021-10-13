#include <stdio.h>
#include <assert.h>
char *StrCpy(char *dest, const char *src);
int main()
{
	char dest[10] = {0};
	printf("dest is now: %s\n", StrCpy(dest, "hello"));
	return 0;	
}

char *StrCpy(char *dest, const char *src)
{
	char *dest_ptr = dest ;
	assert(dest && src);
	while ('\0' != *src)
	{
		*dest = *src;
		++dest;
		++src;
	}
	
	*dest = '\0';
	return dest_ptr;
}
