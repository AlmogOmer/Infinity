#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
int Atoi (const char *str, int base);
void test ();
int main()
{
	test();
	return 0;
}

void test ()
{
	assert(atoi("123 45")== Atoi("123 45", 10));
	assert(atoi("123/45")== Atoi("123/45", 10));
	assert(atoi("123:45")== Atoi("123:45", 10));
	assert(atoi("1234")== Atoi("1234", 10));
	assert(123== Atoi("7B", 16));
	
}
int Atoi (const char *str, int base)
{
	int i = 0;
	int result = 0;
	int len = strlen(str);
	for (i =0; i< len ; ++i)
	{
		if (((str[i] < 'A') && (str[i]>'9')) || (str[i] > 'z') || (str[i]<'0'))
		{
			break;
		}
		else if (str[i] >= 'A' && str[i] <= 'Z')
		{
			result = base*result + ((str[i]-'A')+10) ;
		}
		else if (str[i] >= 'a' && str[i] <= 'z')
		{
			result = base*result + ((str[i]-'a')+10) ;
		}
		else
		{	
			result = base*result + (str[i]-'0') ;	
		}
		
		
	}
	return result;
}

