#include <stdio.h>
#include <assert.h>
size_t StrSpn(const char *str1, const char *str2);
char *StrChr(const char *str, int c);
int main()
{
	printf("%ld\n", StrSpn("abbbcctrdcdefg", "abc"));
	return 0;	
}

size_t StrSpn(const char *str1, const char *str2)
{
	size_t counter = 0;
	assert(str1 && str2);
	while (StrChr(str2, *str1) != NULL)
		{
			++counter;
			++str1;
		}
	
	return counter;
		
}
		
char *StrChr(const char *str, int c)
{
	assert(str);
	while ( *str != c)
	{
		if ('\0' == *str && c != '\0')
		{
			return NULL;
		}
		++str;
	}
	
	return (char*)str;		
}




