#include <stdio.h>
#include <stdlib.h>

typedef struct snode 
{
    int data;
    struct snode *next;
}snode;


snode *create_node(int data);
int main()
{
    
    snode *head = NULL;
    snode *temp = NULL;
    int x = 1;
    int y = 2;
    int z = 3;
    int g = 4;
    head = create_node(x);
    temp  = head;
    temp->next = create_node(y);
    
    temp = temp->next;
    temp->next = create_node(z);
    
    temp = temp->next;
    temp->next = create_node(g);
    
    temp=head;
    while(temp != NULL)
    {
        printf("%d", temp->data);
        temp = temp->next;
    }
    return 0;
    
}


snode *create_node(int data)
{
    
    snode *new_node = NULL;
    new_node = (snode*)malloc(sizeof(snode));
    new_node->data =  data;
    new_node->next = NULL;
    return new_node;
}

