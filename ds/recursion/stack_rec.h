#include <stddef.h>

typedef struct Stack stacki_t;

/*function to create a stack of given capacity. It initializes size of stack as 0*/
stacki_t* createStack(size_t capacity);

/*Stack is full when top is equal to the last index*/
int isFull(stacki_t* stack);

/*Stack is empty when top is equal to -1*/
int isEmpty(stacki_t* stack);

/*Function to add an item to stack.  It increases top by 1*/
void push(stacki_t* stack, int item);

/*Function to remove an item from stack.  It decreases top by 1*/
int pop(stacki_t* stack);

/* Function to return the top from stack without removing it*/
int peek(stacki_t* stack);

void Print(struct Stack  *stack);

void Stack_sort_insert(stacki_t *stack, int x);

void Sort_stack(stacki_t *stack);



