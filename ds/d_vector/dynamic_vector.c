#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include "dynamic_vector.h"

struct Vector
{
	size_t top;
	size_t capacity;
	size_t type_size;
	void *array;

};

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
	assert(Vector->top==1 && Vector->capacity==1 && VectorGetAccessToElement(Vector,Vector->top )==element);
	
	VectorPushBack(Vector, element);
	assert(Vector->top==2 && Vector->capacity==2 && VectorGetAccessToElement(Vector,Vector->top )==element);
	
	VectorPushBack(Vector, element);
	assert(Vector->top==3 && Vector->capacity==4 && VectorGetAccessToElement(Vector,Vector->top )==element);
	
	VectorPopBack(Vector);
	assert(Vector->top==2 && Vector->capacity==4 && VectorGetAccessToElement(Vector,Vector->top )==element);
	
	VectorReserve(Vector, num);
	assert(Vector->top==2 && Vector->capacity==10 && VectorGetAccessToElement(Vector,Vector->top )==element);
	
	assert(2==VectorSize(Vector));
	
	assert(10==VectorCapacity(Vector));
	
	VectorDestroy(Vector);
	
	return 0;
}


Vector_t *VectorCreate(size_t initial_capacity, size_t type_size)
{
	Vector_t *new_vector = NULL;
	new_vector = (Vector_t *) malloc(sizeof(Vector_t)+ initial_capacity*type_size);
	if (NULL == new_vector)
	{
		printf("allocation failed");
		return NULL;
	}

	new_vector->top = 0;
	new_vector->capacity = initial_capacity;
	new_vector->type_size =  type_size;
	new_vector->array = (void *)(new_vector + 1);
	return new_vector;

}

void VectorDestroy(Vector_t *vector)
{
	free(vector);
	vector = NULL;
}

void VectorPushBack(Vector_t *vector, const void* element)
{
	if (vector->top+1 >= vector->capacity)
		{
			vector->array = (void *) realloc(vector->array,2*vector->capacity*vector->type_size);
		}
		if (NULL == vector->array)
		{
			exit (1);
		}
		
	
	/* first push the data, then increment top */
	memcpy((char*)vector->array + vector->type_size * vector->top, element , vector->type_size);
	vector->top++;

}

void VectorPopBack(Vector_t *vector)
{
	vector->top--;
}

void* VectorGetAccessToElement(Vector_t *vector, size_t idx)
{
	/*vector->array[idx]*/
	return ((char *) vector->array + idx * vector->type_size);
}

void VectorReserve(Vector_t *vector, size_t num)
{
	if (num > vector->capacity)
	{
		vector->array = (void *)realloc(vector->array, num * vector->type_size);
	
		if (NULL == vector->array)
		{
			exit (1);
		}

		vector->capacity = num;
	}
}

size_t VectorSize(Vector_t *vector)
{
	return vector->top;
}

size_t VectorCapacity(Vector_t *vector)
{
	return vector->capacity;

}











