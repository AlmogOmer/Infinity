#include <stdio.h>
#include <assert.h>
size_t StrLen (const char *str);
char *StrnCat(char *dest, const char *src, size_t n);
char *StrnCpy(char *dest, const char *src, size_t n);
int main()
{
	char dest[20] = {'a','b'};
	printf("%s\n", StrnCat(dest, "Al5g", 3));
	return 0;	
}

char *StrnCat(char *dest, const char *src, size_t n)
{
	size_t len_dest = StrLen(dest) ;
	char *cat_result = StrnCpy((dest + len_dest), src, n);
	assert(dest && src);
	*(cat_result + len_dest + n) = '\0';
	return (cat_result - len_dest);
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


size_t StrLen (const char *str)
{
	size_t count = 0;
	while (str[count] != '\0')
	{
		++count;
	}
	return count;
}



