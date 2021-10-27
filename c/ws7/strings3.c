#include <stdio.h>
#include "stringh.h"
char *StrStr(const char *haystack, const char *needle)
{
	const char *og_needle = needle;
	size_t len_needle = StrLen(needle);
	assert(haystack && needle);
	while (*haystack != '\0')
	{	
		while (*haystack == *needle)
		{
			if('\0' ==*(needle + 1))
			{
				return (char *)(haystack - (len_needle-1)); 
				/* points to where the needle starts in haystack*/
			}
			
			++haystack;
			++needle;
		}
		++haystack;
		needle = og_needle; /* needle go back to point the first character*/
	}
	return NULL;
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
