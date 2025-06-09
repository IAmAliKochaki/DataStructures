#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "stack.h"

#define ST_ERROR_VALUE INT_MIN

Stack *st_create()
{
    Stack *new_stack = (Stack *)malloc(sizeof(Stack));
    if (!new_stack)
    {
        fprintf(stderr, "st_create: stack creation failed.\n");
        return NULL;
    }

    new_stack->list = ll_create();
    if (!new_stack->list)
    {
        fprintf(stderr, "st_create: stack creation failed.\n");
        free(new_stack);
        return NULL;
    }

    return new_stack;
}
void st_destroy(Stack *stack)
{
    if (!stack)
    {
        fprintf(stderr, "st_destroy: null pointer stack.\n");
        return;
    }

    ll_destroy(stack->list);
    free(stack);
}

void push(Stack *stack, int value)
{
    if (!stack)
    {
        fprintf(stderr, "push: null pointer stack.\n");
        return;
    }
    ll_add_first(stack->list, value);
}
int pop(Stack *stack)
{
    if (!stack)
    {
        fprintf(stderr, "pop: null pointer stack.\n");
        return ST_ERROR_VALUE;
    }

    if (ll_is_empty(stack->list))
    {
        fprintf(stderr, "pop: stack is empty.\n");
        return ST_ERROR_VALUE;
    }

    int pop_value = ll_get(stack->list, 0);
    ll_remove_first(stack->list);
    return pop_value;
}

int peek(Stack *stack)
{
    if (!stack)
    {
        fprintf(stderr, "peek: null pointer stack.\n");
        return ST_ERROR_VALUE;
    }

    if (ll_is_empty(stack->list))
    {
        fprintf(stderr, "peek: stack is empty.\n");
        return ST_ERROR_VALUE;
    }

    return ll_get(stack->list, 0);
}

int st_is_empty(Stack *stack)
{
    if (!stack)
    {
        fprintf(stderr, "st_is_empty: null pointer stack.\n");
        return 1;
    }

    return ll_is_empty(stack->list);
}

int st_size(Stack *stack)
{
    if (!stack)
    {
        fprintf(stderr, "st_size: null pointer stack.\n");
        return 0;
    }

    return ll_size(stack->list);
}
