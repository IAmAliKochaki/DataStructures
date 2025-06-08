#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "stack.h"

#define ST_ERROR_VALUE INT_MIN

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

void push(Stack *stack, int value)
{
    if (!stack)
    {
        fprintf(stderr, "push: null pointer stack.\n");
        return;
    }

    if (stack->top == stack->capacity)
    {
        fprintf(stderr, "push: stack is full.\n");
        return;
    }

    stack->array[stack->top++] = value;
}

int pop(Stack *stack)
{
    if (!stack)
    {
        fprintf(stderr, "pop: null pointer stack.\n");
        return ST_ERROR_VALUE;
    }

    if (stack->top == 0)
    {
        fprintf(stderr, "pop: stack is empty.\n");
        return ST_ERROR_VALUE;
    }

    return stack->array[--stack->top];
}

int peek(Stack *stack)
{
    if (!stack)
    {
        fprintf(stderr, "peek: null pointer stack.\n");
        return ST_ERROR_VALUE;
    }

    if (stack->top == 0)
    {
        fprintf(stderr, "peek: stack is empty.\n");
        return ST_ERROR_VALUE;
    }

    return stack->array[stack->top - 1];
}

int st_is_empty(Stack *stack)
{
    if (!stack)
    {
        fprintf(stderr, "st_is_empty: null pointer stack.\n");
        return 1;
    }

    return stack->top == 0;
}

int st_is_full(Stack *stack)
{
    if (!stack)
    {
        fprintf(stderr, "st_is_full: null pointer stack.\n");
        return 1;
    }

    return stack->top == stack->capacity;
}
