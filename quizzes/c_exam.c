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
    val = val ^ (1<<n);
    return val;
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

    while (str1[i] == str2[i])
    {
        ++i;
    }

    return (i == len1);
}

char *Strcpy (char *dest, char *src)
{
    int i = 0;
    for (i = 0; src[i] != '\0'; ++i)
    {
        dest[i] = src [i];
    }

    dest[i] = '\0';

    return dest;
}


char *Strncpy (char *dest, char *src, int n)
{
    int i = 0;
    for (i = 0; i < n && src[i] != '\0'; ++i)
    {
        dest[i] = src [i];
    }

    dest[i] = '\0';

    return dest;
}

char *Strcat (char *dest, char *src)
{
    int len_dest = strlen(dest);
    char *result = strcpy(dest + len_dest, src);

    return (result - len_dest);
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
    int val = 7;
    unsigned int n = 2;
    unsigned char u = 7;
    char byte = 7;
    unsigned nbits = 3;
    int y = 4;
    int x = 1234;
    int *px = &x;
    int *py = &y;
    int **p1 = &px;
    int **p2 = &py;
    char *str = "almog";
    char *str1 = "almog";
    char *str2 = "almog";
    char dest[10];
    char *src = "aaaaa";
    char string [10];
    int number = 2;
   

    FlipDigitsInNum (num);

    FlipBit (val, n);

    CountBit (u);

    RotateLeft (byte,  nbits); 

    SwapPointers (p1, p2);

    Strlen(str);

    Strcmp(str1, str2);

    Strcpy (dest, src);

    Strncpy (dest, src, y);

    Strcat (dest, src);

    GetNFibonacciElement(n);

    IntToString (x, string);

    multiply8(number);

    swap (px, py);

    swap2 (px, py);

    swap3 (px, py);

    return 0;

}



