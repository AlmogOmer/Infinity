#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
char *SrtDup(const char *str);
size_t StrLen (const char *str);
char *StrCpy(char *dest, const char *src);
int main()
{
	char *ptr = NULL;
	ptr = SrtDup("Abc");
	printf("%s\n",ptr);
	free(ptr);
	return 0;
}

char *SrtDup(const char *str)
{
	
	int num = StrLen(str);
	char *dest = (char*)malloc((num+1)*sizeof(char));/* num+1 so it will include the \0 also*/
	assert(str);
	
	if (dest == NULL)
	{
		return NULL;
	}
	StrCpy(dest, str);
	return dest;
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
