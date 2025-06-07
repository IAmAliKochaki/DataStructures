#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

Stack *st_create(size_t capacity)
{
    Stack *new_stack = (Stack *)malloc(sizeof(Stack));
    if (!new_stack)
    {
        fprintf(stderr, "st_create: stack creation failed.\n");
        return NULL;
    }

    new_stack->array = (int *)malloc(capacity * sizeof(int));
    if (!new_stack->array)
    {
        fprintf(stderr, "st_create: stack creation failed.\n");
        free(new_stack);
        return NULL;
    }

    new_stack->capacity = capacity;
    new_stack->top = 0;
    return new_stack;
}
void st_destroy(Stack *stack)
{
    if (!stack)
    {
        fprintf(stderr, "st_destroy: null pointer stack.\n");
        return;
    }

    free(stack->array);
    free(stack);
}