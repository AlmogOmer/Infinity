#include <stdio.h>
#include "stack.h"
#include <assert.h>
#include <stdlib.h>		


Stack_t *StackCreate(size_t capacity)
{
	Stack_t *new_stack = NULL;
	new_stack = (Stack_t *) malloc(sizeof(Stack_t)+ sizeof(void *)*capacity);
	
	if (NULL == new_stack)
	{
		printf("allocation failed");
		return NULL;
	}
	
	new_stack->array = (void**)(new_stack+1);
	new_stack->capacity = capacity;
	new_stack->top = 0;

	return new_stack;
}


void StackDestroy(Stack_t *stack)
{
	assert(stack);
	free(stack);
	stack = NULL;
	
}

void StackPush(Stack_t *stack, void* new_element)
{
	assert(stack && new_element);
	assert(stack->top != stack->capacity);
	stack->array[++stack->top] = new_element;
}

void StackPop(Stack_t *stack)
{
	assert(stack);
	assert(StackIsEmpty(stack) != 1);
	--stack->top;
}

void* StackPeek(Stack_t *stack)
{
	assert(stack);
	return (stack->array[stack->top]);
}

int StackIsEmpty(Stack_t *stack)
{
	assert(stack);
	return (stack->top == 0);

}

size_t StackSize(Stack_t *stack)
{
	assert(stack);
	return stack->top;
}

size_t StackCapacity(Stack_t *stack)
{
	assert(stack);
	return stack->capacity;
}
