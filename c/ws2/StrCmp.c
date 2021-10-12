#include <stdio.h>
#include <assert.h>
int SrtCmp(const char *str1, const char *str2);
int main()
{
	printf("the result of comapring the strings is: %d\n",SrtCmp("abc", "abcs"));
	return 0;
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
		






