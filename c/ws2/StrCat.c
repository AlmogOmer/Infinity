#include <stdio.h>
#include <assert.h>
char *StrCat(char *dest, const char *src);
size_t StrLen (const char *str);
char *StrCpy(char *dest, const char *src);
int main()
{
	char dest[20] = {'a','b'};
	printf("%s\n", StrCat(dest, "Al"));
	return 0;	
}

char *StrCat(char *dest, const char *src)
{
	size_t len_dest = StrLen(dest) ;
	assert(dest && src);

	return (StrCpy((dest + len_dest), src)- len_dest);
}

size_t StrLen (const char *str)
{
	size_t count = 0;
	while (str[count] != '\0')
	{
		++count;
	}
	return count;
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


