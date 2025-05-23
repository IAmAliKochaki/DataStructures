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
    fprintf(stderr, "da_destroy: null array pointer\n");
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
    if (!arr)
    {
        fprintf(stderr, "da_set: null array pointer\n");
        return;
    }
    if (idx >= arr->size)
    {
        fprintf(stderr, "da_set: index %zu out of bounds (size = %zu)\n", idx, arr->size);
        return;
    }
    arr->data[idx] = value;
}

int da_index_of(DynamicArray *arr, int value)
{
    if (!arr)
    {
        fprintf(stderr, "da_index_of: null array pointer\n");
        return -1;
    }

    for (size_t idx = 0; idx < arr->size; idx++)
        if (arr->data[idx] == value)
            return (int)idx;
    return -1;
}

int da_index_of_nth(DynamicArray *arr, int value, int n)
{
    if (!arr)
    {
        fprintf(stderr, "da_index_of_nth: null array pointer\n");
        return -1;
    }
    if (n < 0)
    {
        fprintf(stderr, "da_index_of_nth: n must be non-negative\n");
        return -1;
    }

    for (size_t idx = 0, occurrence = 0; idx < arr->size; idx++)
        if (arr->data[idx] == value && occurrence++ == n)
            return idx;
    return -1;
}

int da_contains(DynamicArray *arr, int value)
{
    if (!arr)
    {
        fprintf(stderr, "da_contains: null array pointer\n");
        return 0;
    }

    for (size_t idx = 0; idx < arr->size; idx++)
        if (arr->data[idx] == value)
            return 1;
    return 0;
}

int da_count_value(DynamicArray *arr, int value)
{
    if (!arr)
    {
        fprintf(stderr, "da_count_value: null array pointer\n");
        return 0;
    }

    int count = 0;
    for (size_t idx = 0; idx < arr->size; idx++)
        if (arr->data[idx] == value && ++count)
            ;
    return count;
}

static int double_capacity(DynamicArray *arr)
{
    int *temp_data = (int *)realloc(arr->data, 2 * (arr->capacity) * sizeof(int));
    if (temp_data)
    {
        arr->data = temp_data;
        arr->capacity *= 2;
        return 1;
    }
    return -1;
}

static int is_full(DynamicArray *arr)
{
    return arr->size == arr->capacity;
}

void da_add_first(DynamicArray *arr, int value)
{
    if (!arr)
    {
        fprintf(stderr, "da_add_first: null array pointer\n");
        return;
    }

    if (is_full(arr))
        if (double_capacity(arr) != 1)
        {
            fprintf(stderr, "da_add_first: failed to allocate memory\n");
            return;
        }

    for (size_t idx = arr->size; idx > 0; idx--)
        arr->data[idx] = arr->data[idx - 1];
    arr->data[0] = value;
    arr->size++;
}

void da_add_last(DynamicArray *arr, int value)
{
    if (!arr)
    {
        fprintf(stderr, "da_add_last: null array pointer\n");
        return;
    }

    if (is_full(arr))
        if (double_capacity(arr) != 1)
        {
            fprintf(stderr, "da_add_last: failed to allocate memory\n");
            return;
        }

    arr->data[arr->size++] = value;
}
