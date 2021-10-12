#include <stdio.h>
#include <assert.h>
size_t StrLen (const char *str);
int main ()
{
	printf("the length of the string is: %ld\n",StrLen("abc"));
	return 0;
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
	
