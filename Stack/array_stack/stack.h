#ifndef STACK_H
#define STACK_H

#include <stddef.h>

// Struct representing a stack implemented using an array.
typedef struct
{
    size_t top;
    size_t capacity;
    int *array;
} Stack;

Stack *st_create(size_t capacity); // Create a new stack with the given capacity.
void st_destroy(Stack *stack); // Free the memory used by the stack.

void push(Stack *stack, int value); // Pushes an integer value onto the stack.
int pop(Stack *stack); // Removes and returns the top element from the stack.
int peek(Stack *stack); // Returns the top element of the stack without removing it.

int st_is_empty(Stack *stack); // Return 1 if the array is empty, 0 otherwise.
int st_is_full(Stack *stack); // Return 1 if the array is full, 0 otherwise.

#endif // STACK_H
