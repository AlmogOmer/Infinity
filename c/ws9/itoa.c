#include<stdio.h>
#include<string.h>
char *itoa (int value, char* str, int base);
char *reversed_str (char *str);
void swap(char *x, char *y);
int main()
{
	int value = 12345678;
	char str[256] = {0};
	int base = 10;
	printf("%s\n", itoa(value, str, base));
	return 0;
}


char *itoa (int value, char* str, int base)
{
	int j = 0;
	int temp = 0;
	while (value != 0)
	{
		temp = value % base;
		str[j] = temp + '0';
		++j;
		value = value/base;
	}
	reversed_str(str);
	return str;
}

char *reversed_str (char *str)
{
	size_t i = strlen(str);
	char *end = str + i - 1;
	char *start = str;

	while (end > start)
	{
		swap(start, end);
		
		++start;
		--end;
	}
	
	return str;

}


void swap(char *x, char *y)
{
	*x ^= *y;
	*y ^= *x;
	*x ^= *y;
}



