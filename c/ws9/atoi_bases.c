#include<stdio.h>
#include<string.h>
int atoi (const char *str, int base);
int main()
{
	const char str[] = "123 45";
	int base = 10;
	printf("%d\n", atoi (str, base));
	return 0;
}

void test (const char *str)
{

}
int atoi (const char *str, int base)
{
	int i = 0;
	int result = 0;
	int len = strlen(str);
	if (str[i] == ' ')
		{
			len = len ;
		}
	int temp = 1;
	for (i =( len-1 ); i>=0 ; --i)
	{
		
		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			result = result + temp*((str[i]-'A')+10) ;
		}
		else
		{	
			result = result + temp*(str[i]-'0') ;	
		}
		
		temp = temp*base;
	}
	return result;
}

