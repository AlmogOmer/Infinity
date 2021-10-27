#include <stdio.h>
#include "stringh.h"
char *Srtchr(const char *str, int c)
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
	

int SrtCmp(const char *str1, const char *str2)
{
	assert(str1 && str2);
	while (*str1 == *str2)	
	{
		if (*str1 == '\0')
		{
			return 0;
		}
		
		++str1;
		++str2;
	}
	
	return (*str1 - *str2);
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
