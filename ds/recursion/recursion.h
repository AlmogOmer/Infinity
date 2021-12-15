#ifndef RECURSION_H
#define RECURSION_H

#include <stdlib.h>

typedef struct Node
{
    struct Node* next;
    int data;

}node_t;

extern int Fibonacci(int element_index);

extern node_t *FlipList(node_t* list);

extern void Sort_stack(stack_t stack);

extern int Strlen_recu(char *str);

extern int Srtcmp_recu(const char *str1, const char *str2);

extern char *Strcpy_recu(char *dest, const char *src);

extern char *Strcat_recu(char *dest, const char *src);

extern char *Strstr_recu(char *haystack, char *needle);

#endif	


