#include <stdlib.h>
#include "dynamic_array.h"

DynamicArray *da_create(size_t initial_capacity)
{
    DynamicArray *new_da = (DynamicArray *)malloc(sizeof(DynamicArray));
    if (!new_da)
        return NULL;

    new_da->data = (int *)malloc(initial_capacity * sizeof(int));
    if (!new_da->data)
    {
        free(new_da);
        return NULL;
    }

    new_da->capacity = initial_capacity;
    new_da->size = 0;
    return new_da;
}

void da_destroy(DynamicArray *arr)
{
    if (arr)
    {
        free(arr->data);
        free(arr);
    }
}
