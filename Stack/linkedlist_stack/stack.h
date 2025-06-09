#ifndef STACK_H
#define STACK_H

#include "LinkedList/linkedlist.h"

typedef struct
{
    linkedlist *list;
} Stack;

Stack *st_create(); // Create a new stack.
void st_destroy(Stack *stack); // Free the memory used by the stack.

void push(Stack *stack, int value); // Pushes an integer value onto the stack.
int pop(Stack *stack); // Removes and returns the top element from the stack.
int peek(Stack *stack); // Returns the top element of the stack without removing it.

int st_is_empty(Stack *stack); // Return 1 if the array is empty, 0 otherwise.
int st_size(Stack *stack); // Return the current number of elements in the stack.


#endif // STACK_H