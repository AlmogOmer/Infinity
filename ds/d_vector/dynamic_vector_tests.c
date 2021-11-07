#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "dynamic_vector.h"

int main()
{
	
	size_t initial_capacity, type_size, num;
	Vector_t *Vector = NULL;
	int element_value = 8;
	int *element = NULL;
	element = &element_value;
	*element = element_value;
	initial_capacity = 1;
	type_size = 4;
	num = 10; 
	
	
	Vector  = VectorCreate(initial_capacity, type_size);
	assert(Vector->top==0 && Vector->capacity==1 && Vector->array!=NULL);
	
	VectorPushBack(Vector, element);
	assert(Vector->top==1 && Vector->capacity==1) ;
	
	VectorPushBack(Vector, element);
	assert(Vector->top==2 && Vector->capacity==2) ;
	
	assert(*element==*(int *)VectorGetAccessToElement(Vector, 1));
	
	VectorPushBack(Vector, element);
	assert(Vector->top==3 && Vector->capacity==4);
	
	VectorPushBack(Vector, element);
	assert(Vector->top==4 && Vector->capacity==4);
	
	VectorPopBack(Vector);
	assert(Vector->top==3 && Vector->capacity==4);
	
	assert(3==VectorSize(Vector));
	
	assert(4==VectorCapacity(Vector));
	
	VectorPopBack(Vector);
	assert(Vector->top==2 && Vector->capacity==4);
	
	VectorPopBack(Vector);
	assert(Vector->top==1 && Vector->capacity==2);
	
	VectorReserve(Vector, num);
	assert(Vector->top==1 && Vector->capacity==10);
	
	VectorDestroy(Vector);
	
	return 0;
}

