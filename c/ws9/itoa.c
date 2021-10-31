#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>
char *Itoa (int value, char* str, int base);
char *reversed_str (char *str);
void swap(char *x, char *y);
void test();
int main()
{
	test();
	return 0;
}

void test()
{
	char str[256] = {0};
	char str_result1[]= "123";
	char str_result2[]= "7B";
	char str_result3[]= "-123";
	printf("%d\n",strcmp(str_result2, Itoa(0x7B, str, 16)));
	printf("%d\n",strcmp(str_result1, Itoa(123, str, 10)));
	printf("%d\n",strcmp(str_result3, Itoa(-123, str, 10)));

}
char *Itoa (int value, char* str, int base)
{
	int j = 0;
	int temp = 0;
	int is_neg = 0;
	if (value < 0)
	{
		value = -value;
		str[j] = '-'; 
		++j;
		is_neg = 1;
	}
	while (value != 0)
	{
		temp = value % base;
		if (temp < 10)
		{
			temp = temp + '0';
		}
		else
		{
			temp = temp + 'A' - 10;
		}
		str[j] = temp;
		++j;
		value = value/base;
	}
	if (is_neg)
		reversed_str(str+1);
	else
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



