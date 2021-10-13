#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
int SrtCasecmp(const char *str1, const char *str2);
int main()
{
	printf("the result of comapring the strings is: %d\n",SrtCasecmp("Abc", "abc"));
	return 0;
}

int SrtCasecmp(const char *str1, const char *str2)
{
	assert(str1 && str2);
	while (tolower(*str1) == tolower(*str2))	
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
