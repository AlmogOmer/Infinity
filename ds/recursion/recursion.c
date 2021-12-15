#include <stdio.h>
#include<assert.h>
#include<string.h>
#include "recursion.h"


int Fibonacci(int element_index)
{
    if(element_index <= 2)
    {
        return element_index -1;
    }

    return (Fibonacci(element_index - 1)+ Fibonacci(element_index - 2));

}


node_t *FlipList(node_t* node)
{
    node_t *temp;
    if(node->next == NULL)
    {
        return node;
    }
    
    temp = FlipList(node->next);
    node->next->next = node;
    node->next = NULL;

    return temp;

}

extern void Sort_stack(stack_t stack);

int Strlen_recu(char *str)
{
    if (*str == '\0')
    {
        return 0;
    }

    return (1 + Strlen_recu(str+1));
}

int Srtcmp_recu(const char *str1, const char *str2)
{
    if (*str1 != *str2)
    {
        return (*str1 - *str2);
    }

    if (*str1 == '\0')
    {
        return 0;
    }

    return Srtcmp_recu(str1 +1, str2+1);
}

char *Strcpy_recu(char *dest, const char *src)
{
    *dest = *src;
    if (*src == '\0')
    {
        return dest;
    }

    return Strcpy_recu(dest +1, src+1) -1;

}

char *Strcat_recu(char *dest, const char *src)
{
    if (*dest)
    {
        return Strcat_recu(dest +1, src) - 1;
    }
    
    return Strcpy_recu(dest,src);

}

char *Strstr_recu(char *haystack, char *needle)
{
    if(*needle == '\0')
    {
        return haystack;
    }
    
    if(*haystack == '\0')
    {
        return NULL;
    }

    if(*haystack == *needle)
    {
        return Strstr_recu(haystack+1, needle+1)-1;
    }
   
    return Strstr_recu(haystack+1, needle);
}




