#include <stdio.h>
#include <assert.h>
char *StrStr(const char *haystack, const char *needle);
size_t StrLen (const char *str);
int main()
{
	printf("%s\n", StrStr("abcdefhtgefgtt", "efg"));
	return 0;	
}

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

size_t StrLen (const char *str)
{
	size_t count = 0;
	while (str[count] != '\0')
	{
		++count;
	}
	return count;
}



