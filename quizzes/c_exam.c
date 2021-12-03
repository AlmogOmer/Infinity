#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include<string.h>

int FlipDigitsInNum (int num)
{
    int result = 0;
    int is_neg = 1;
    if (num < 0)
    {
        is_neg = -1;
        num = -num;
    }

    while (num > 0)
    {
        result = 10 * result + num % 10;
        num = num / 10;
    }

    return (is_neg * result);
}

int FlipBit (int val, unsigned int n)
{
    return (val ^ (1<<(n-1)));
}

int CountBit (unsigned char x)
{
    int counter = 0;
    while (x)
    {
        counter++;
        x = x & (x-1);

    }
    return counter;
}

char RotateLeft (char byte, unsigned nbits)
{
    assert (nbits <= 8);
    return (byte<<nbits) | (byte>>(8-nbits));
}

void SwapPointers (int **p1, int **p2)
{
    int *temp = NULL;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int Strlen(char *str)
{
    int counter = 0;
    int i = 0;
    for (i = 0; str[i] != '\0'; ++i)
    {
        ++counter;
    }
    return counter;
}


int Strcmp(char *str1, char *str2)
{
    int i = 0;
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    if (len1 != len2)
    {
        return 0;
    }

    while (str1[i] != '\0' && str1[i] == str2[i])
    {
        ++i;
    }

    return (i == len1);
}

char *Strcpy (char *dest, char *src)
{
    
    char *dest_ptr = dest ;
	while ('\0' != *src)
	{
		*dest = *src;
		++dest;
		++src;
	}
	
	*dest = '\0';
	return dest_ptr;
    
    
    
    /*int i = 0;
    for (i = 0; src[i] != '\0'; ++i)
    {
        dest[i] = src[i];
    }

    dest[i] = '\0';

    return dest;*/
}


char *Strncpy (char *dest, char *src, int n)
{
    char *dest_ptr = dest ;
	assert(dest && src);
	while (('\0' != *src) && n)
	{
		*dest = *src;
		++dest;
		++src;
		--n;
	}
	
	while (n)
	{
		*dest = '\0';
		++dest;
		--n;
	}
	
	return dest_ptr;
    
    
    
    /*int i = 0;
    for (i = 0; i < n && src[i] != '\0'; ++i)
    {
        dest[i] = src [i];
    }

    dest[i] = '\0';

    return dest;*/
}

char *Strcat (char *dest, char *src)
{
    size_t len_dest = strlen(dest) ;

	return (strcpy((dest + len_dest), src)- len_dest);
    
    
    /*int len_dest = strlen(dest);
    char *result = strcpy(dest + len_dest, src);

    return (result - len_dest);*/
}

unsigned long GetNFibonacciElement(unsigned int n)
{
    unsigned long next = 0;
    unsigned long prev = 1;
    unsigned long curr = 0;

    while (n>0)
    {
        next = prev + curr;
        prev = curr;
        curr = next;

        --n;
    }

    return curr;
}

char *IntToString (int x, char *str)
{
    sprintf(str, "%d", x);
    return str;
}

int multiply8(int num)
{
    int is_neg = 1;
    if (num<0)
    {
        num = -num;
        is_neg = -1;
    }

    return (is_neg * (num<<3));
}

void swap ( int *x, int *y)
{
    *x = *x ^ *y;
    *y = *y ^ *x;
    *x = *x ^ *y;
}

void swap2 ( int *x, int *y)
{
    *x = *x + *y;
    *y = *x - *y;
    *x = *x - *y;
}

void swap3 ( int *x, int *y)
{
    int temp = 0;
    temp = *x;
    *x = *y;
    *y = temp;
}


int main()
{
    int num = 29;
    int val = 1;
    unsigned int n = 1;
    unsigned char u = 7;
    char byte = 1;
    unsigned nbits = 2;
    int y = 4;
    int x = 1234;
    int *px = &x;
    int *py = &y;
    int **p1 = &px;
    int **p2 = &py;
    char *str = "almog";
    char *str1 = "almog";
    char *str2 = "almog";
    char dest1[10] ;
    char dest2[10];
    char dest[40] = {'a','b'};
    char *src = "aaaaa";
    char string [10];
    int number = 2;
   

    assert(92 == FlipDigitsInNum (num));
    
    assert(0 == FlipBit(val, n));

    assert(3 == CountBit(u));

    assert(4 == RotateLeft(byte,  nbits)); 
  
    SwapPointers(p1, p2);
    
    assert ((**p1 == 4) && (**p2 == 1234));

    assert(5 == Strlen(str));

    assert(1 == Strcmp(str1, str2));

    assert(0 == strcmp("aaaaa",Strcpy(dest1, src)));

    assert(0 == strcmp("aaaa",Strncpy(dest2, src, y)));

    assert(0 == strcmp("abaaaaa",Strcat(dest, src)));

    assert(1 == GetNFibonacciElement(n));

    assert(0 == strcmp("1234", IntToString(x, string)));

    assert(16 == multiply8(number));

    swap(px, py);
    assert ((*px == y) && (*py == x));
    
    swap2(px, py);
    assert ((*px == y) && (*py == x));
    
    swap3(px, py);
    assert ((*px == y) && (*py == x));

    return 0;

}



