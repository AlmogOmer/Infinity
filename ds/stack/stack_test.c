#include <stdio.h>
#include "stack.h"
#include <assert.h>
#include <stdlib.h>		
	


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
	
	
	return 0;
}




