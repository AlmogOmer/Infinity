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


Vector_t *VectorCreate(size_t initial_capacity, size_t type_size)
{
	Vector_t *new_vector = NULL;
	new_vector = (Vector_t *) malloc(sizeof(Vector_t));
	if (NULL == new_vector)
	{
		printf("allocation failed");
		return NULL;
	}
	new_vector->array = (void *)malloc(initial_capacity*type_size);
	
	if (NULL == new_vector->array)
	{
		printf("allocation failed");
		return NULL;
	}
	new_vector->top = 0;
	new_vector->capacity = initial_capacity;
	new_vector->type_size =  type_size;
	
	return new_vector;

}

void VectorDestroy(Vector_t *vector)
{
	assert(vector);
	free(vector->array);
	vector->array = NULL;
	free(vector);
	vector = NULL;
}

void VectorPushBack(Vector_t *vector, const void* element)
{
	assert(vector && element);
	if (vector->top == vector->capacity)
		{
			
			VectorReserve(vector, 2*(vector->capacity));
		
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
	assert(vector);
	vector->top--;
	if (vector->top <= ((vector->capacity)/3))
		{
			vector->capacity = (vector->capacity)/2;
		}
}

void* VectorGetAccessToElement(Vector_t *vector, size_t idx)
{
	
	assert(vector && idx<=vector->capacity);
	return ((char *) vector->array + idx*vector->type_size);
}

void VectorReserve(Vector_t *vector, size_t num)
{
	assert(vector);
	if (num > vector->capacity)
	{
		void *temp = NULL;
		temp = vector->array;
		vector->capacity = num;
		vector->array = (void*)realloc(vector->array, (vector->capacity)*(vector->type_size));
	
		if (NULL == vector->array)
		{
			vector->array = temp;
			exit (1);
		}

	}
}

size_t VectorSize(Vector_t *vector)
{
	assert(vector);
	return vector->top;
}

size_t VectorCapacity(Vector_t *vector)
{
	assert(vector);
	return vector->capacity;

}











