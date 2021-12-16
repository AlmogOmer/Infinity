#include <limits.h>
#include <stdlib.h>
#include "stack_rec.h"
#include <stdio.h>

struct Stack{
    int top;
    size_t capacity;
    int* array;
};
 

stacki_t* createStack(size_t capacity)
{
    stacki_t *stack = (stacki_t*)malloc(sizeof(stacki_t));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}
 

int isFull(stacki_t* stack)
{
    return stack->top == (int)stack->capacity - 1;
}
 

int isEmpty(stacki_t* stack)
{
    return stack->top == -1;
}

void push(stacki_t* stack, int item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
}

int pop(stacki_t* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top--];
}

int peek(stacki_t* stack)
{
    if (isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}


void Sort_stack(stacki_t *stack)
{
    if (!isEmpty(stack))
    {
        int temp = pop(stack);

        Sort_stack(stack);

        Stack_sort_insert(stack, temp);
    }

}

void Stack_sort_insert(stacki_t *stack, int x)
{
    int temp;
    if (isEmpty(stack) || x > peek(stack))
    {
        push(stack, x);
    }
    else
    {
        temp = pop(stack);
        Stack_sort_insert(stack, x);

        push(stack, temp);
    }
}

void Print(struct Stack  *stack)
{
    int i;

    for(i = 0; i < stack->top + 1; i++)
    {
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}



