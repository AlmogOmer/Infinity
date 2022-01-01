#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "dynamic_vector.h"
void test(void);

int main()
{
	test();
	return 0;
}

void test()
{
    Vector_t *vector = VectorCreate(10, sizeof(long));
    long a = 4;
    long b = 50;
    long c = -23;
    
    VectorPushBack(vector, &a);
    if(!(4 == *(long*)VectorGetAccessToElement(vector, 0)))
    {
    	printf("fail in %d\n", __LINE__);
    }
    
    if(!(10 == VectorCapacity(vector)))
    {
    	printf("fail in %d\n", __LINE__);
    }
    
    if(!(1 == VectorSize(vector)))
    {
    	printf("fail in %d\n", __LINE__);
    }
    
    VectorPushBack(vector, &b);
    
    if(!(2 == VectorSize(vector)))
    {
    	printf("fail in %d\n", __LINE__);
    }

    if(!(50 == *(long*)VectorGetAccessToElement(vector, 1)))
    {
    	printf("fail in %d\n", __LINE__);
    }
    
        VectorPushBack(vector, &c);
        
       if(!(3 == VectorSize(vector)))
    {
    	printf("fail in %d\n", __LINE__);
    }
    
     if(!(-23 == *(long*)VectorGetAccessToElement(vector, 2)))
    {
    	printf("fail in %d\n", __LINE__);
    }
    
    if(!(50 == *(long*)VectorGetAccessToElement(vector, 1)))
    {
    	printf("fail in %d\n", __LINE__);
    }
    
    if(!(4 == *(long*)VectorGetAccessToElement(vector, 0)))
    {
    	printf("fail in %d\n", __LINE__);
    }
    
    VectorPopBack(vector);
    
    if(!(2 == VectorSize(vector)))
    {
    	printf("fail in %d\n", __LINE__);
    }
    
    if(!(5 == VectorCapacity(vector)))
    {
    	printf("fail in %d\n", __LINE__);
    }
    
    VectorReserve(vector, 5);
    
    if(!(5 == VectorCapacity(vector)))
    {
    	printf("fail in %d\n", __LINE__);
    }
    
    VectorPushBack(vector, &c);
    
     if(!(-23 == *(long*)VectorGetAccessToElement(vector, 2)))
    {
    	printf("fail in %d\n", __LINE__);
    }
    
    VectorReserve(vector, 100);
        
    if(!(100 == VectorCapacity(vector)))
    {
    	printf("fail in %d\n", __LINE__);
    }
    
    VectorPopBack(vector);
    
    if(!(2 == VectorSize(vector)))
    {
    	printf("fail in %d\n", __LINE__);
    }
    
    
    VectorDestroy(vector);
    
}
