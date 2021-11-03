#include <stdio.h>
#include "stack.h"
#include <assert.h>
#include <stdlib.h>		
#include <string.h>		


struct Stack
{
	size_t capacity;
	size_t top;            /* index of the last variable*/
	void **array;
};

int main()
{
	size_t capacity;
	int first_element, second_element;
	Stack_t *Stack = NULL;
	capacity = 10;
	first_element = 2; 
	second_element = 4; 
	
	Stack  = StackCreate(capacity);
	assert(Stack->top==0 && Stack->capacity==10 && Stack->array!=NULL);
	
	StackPush(Stack, &first_element);
	assert(Stack->top==1 && Stack->array[Stack->top]== &first_element);
	
	StackPush(Stack, &second_element);
	assert(Stack->top==2 && Stack->array[Stack->top]== &second_element);
	
	StackPop(Stack);
	assert(Stack->top==1 && Stack->array[Stack->top]== &first_element);
	
	assert(StackPeek(Stack)==&first_element);
	
	assert(0==StackIsEmpty(Stack));
	
	assert(1==StackSize(Stack));
	
	assert(10==StackCapacity(Stack));
	
	StackDestroy(Stack);
	assert(Stack->array==NULL);
	/*assert(Stack==NULL);*/
	
	return 0;


}

Stack_t *StackCreate(size_t capacity)
{
	Stack_t *new_stack = NULL;
	new_stack = (Stack_t *) malloc(sizeof(Stack_t));
	
	if (NULL == new_stack)
	{
		printf("allocation failed");
		return NULL;
	}
	
	new_stack->array = (void **)malloc(sizeof(void *)*capacity);
	if (NULL == new_stack->array)
	{
		printf("allocation failed");
		return NULL;
	}
	
	new_stack->capacity = capacity;
	new_stack->top = 0;

	return new_stack;
}


void StackDestroy(Stack_t *stack)
{
	assert(stack);
	free(stack->array);
	stack->array = NULL;
	free(stack);
	stack = NULL;
}

void StackPush(Stack_t *stack, void* new_element)
{
	assert(stack && new_element);
	if (stack->top == stack->capacity)
		return;
	stack->array[++stack->top] = new_element;
}

void StackPop(Stack_t *stack)
{
	assert(stack);
	if (StackIsEmpty(stack))
		return;
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
	if (stack->top == 0)
		return 1;
	return 0;

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





















