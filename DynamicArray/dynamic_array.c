#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
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

int da_get(DynamicArray *arr, size_t idx)
{
    if (arr)
    {
        if (idx >= arr->size)
        {
            fprintf(stderr, "da_get: index %zu out of bounds (size = %zu)\n", idx, arr->size);
            return INT_MIN;
        }
        return arr->data[idx];
    }
    fprintf(stderr, "da_get: null array pointer\n");
    return INT_MIN;
}

void da_set(DynamicArray *arr, size_t idx, int value)
{
    if (idx >= arr->size)
    {
        fprintf(stderr, "da_set: index %zu out of bounds (size = %zu)\n", idx, arr->size);
        return;
    }
    arr->data[idx] = value;
}
