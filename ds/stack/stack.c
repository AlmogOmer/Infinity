#include <stdio.h>
#include "stack.h"
#include <assert.h>
#include <stdlib.h>		



struct Stack
{
	size_t capacity;
	size_t top;            /* index of the last variable*/
	void **array;
};

/*int main()
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
	
	
	return 0;


}*/

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
