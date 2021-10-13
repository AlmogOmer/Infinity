#include <stdio.h>
int palindrom(const char *str);
size_t StrLen (const char *str);
int main()
{
	printf("%d",palindrom("abcdcba"));
	return 0;
}

int palindrom (const char *str)
{
	size_t len_str = StrLen(str);
	size_t i = 0;
	for (i = 0; i < len_str/2; ++i)
	{
		if (str[i] != str[len_str-1-i])
			return 0;
	}
	return 1;
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
	
