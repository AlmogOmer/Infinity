#include<stdio.h>
#include<string.h>
int atoi (const char *str);
int main()
{
	const char str[] = "1234";
	printf("%d\n", atoi (str));
	return 0;
}


int atoi (const char *str)
{
	int i = 0;
	int base = 1;
	int result = 0;
	int len = strlen(str);
	for (i =( len-1 ); i>=0 ; --i)
	{
		result = result + base*(str[i]-'0') ;
		base = base*10;	
	}
	return result;
}

