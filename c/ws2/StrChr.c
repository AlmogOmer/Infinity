#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
char *Srtchr(const char *str, int c);
int main()
{
	printf("%p\n",Srtchr("Abc", '\0'));
	return 0;
}

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
	
	

