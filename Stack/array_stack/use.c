#include <stdio.h>
#include "stack.h"

int main(void)
{
    Stack *stack = st_create(10);
    // Creation failed
    if (!stack)
        return 1;

    for (int i = 1; st_is_full(stack) == 0; i++)
        push(stack, i);

    if (st_is_full(stack))
        printf("stack is full\n");

    printf("\n---------------\n\n");

    if (st_is_empty(stack) == 0)
        printf("top element in stack: %d\n", peek(stack));

    printf("\n---------------\n\n");

    while (st_is_empty(stack) == 0)
        printf("pop: %d\n", pop(stack));

    printf("\n---------------\n\n");

    if (st_is_empty(stack))
        printf("stack is empty\n");

    // Free allocated memory
    st_destroy(stack);
    return 0;
}