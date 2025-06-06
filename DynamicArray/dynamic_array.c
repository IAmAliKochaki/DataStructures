#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "dynamic_array.h"

#define MIN_CAPACITY 16
#define DA_INVALID_SIZE ((size_t)-1)

DynamicArray *da_create(size_t initial_capacity)
{
    DynamicArray *new_da = (DynamicArray *)malloc(sizeof(DynamicArray));
    if (!new_da)
        return NULL;

    if (initial_capacity < MIN_CAPACITY)
        initial_capacity = MIN_CAPACITY;

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
    else
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


int da_index_of_nth(DynamicArray *arr, int value, size_t n)
{
    if (!arr)
    {
        fprintf(stderr, "da_index_of_nth: null array pointer\n");
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


static int change_capacity(DynamicArray *arr, float factor)
{
    size_t new_capacity = (size_t)(arr->capacity * factor);
    if (new_capacity == arr->capacity)
        return 1;

    int *temp_data = (int *)realloc(arr->data, new_capacity * sizeof(int));
    if (temp_data)
    {
        arr->data = temp_data;
        arr->capacity = new_capacity;
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
        // Double the capacity
        if (change_capacity(arr, 2) != 1)
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
        // Double capacity
        if (change_capacity(arr, 2) != 1)
        {
            fprintf(stderr, "da_add_last: failed to allocate memory\n");
            return;
        }

    arr->data[arr->size++] = value;
}


// Shift all elements left from index `start_idx`, then reduce size by 1
static void shift_left_from(DynamicArray *arr, size_t start_idx)
{
    for (size_t i = start_idx; i < arr->size - 1; i++)
        arr->data[i] = arr->data[i + 1];
    arr->size--;
}


static void try_shrink_capacity(DynamicArray *arr)
{
    if (arr->capacity > MIN_CAPACITY && arr->size <= arr->capacity / 4)
    {
        size_t new_capacity = arr->capacity / 2;
        if (new_capacity < MIN_CAPACITY)
            new_capacity = MIN_CAPACITY;

        if (change_capacity(arr, (float)new_capacity / arr->capacity) != 1)
            fprintf(stderr, "try_shrink_capacity: failed to allocate memory\n");
    }
}


void da_remove_first(DynamicArray *arr)
{
    if (!arr)
    {
        fprintf(stderr, "da_remove_first: null array pointer\n");
        return;
    }
    if (arr->size == 0)
    {
        fprintf(stderr, "da_remove_first: array is empty\n");
        return;
    }
    shift_left_from(arr, 0);
    try_shrink_capacity(arr);
}


void da_remove_last(DynamicArray *arr)
{
    if (!arr)
    {
        fprintf(stderr, "da_remove_last: null array pointer\n");
        return;
    }
    if (arr->size == 0)
    {
        fprintf(stderr, "da_remove_last: array is empty\n");
        return;
    }
    arr->size--;
    try_shrink_capacity(arr);
}


void da_remove(DynamicArray *arr, size_t idx)
{
    if (!arr)
    {
        fprintf(stderr, "da_remove: null array pointer\n");
        return;
    }
    if (arr->size == 0)
    {
        fprintf(stderr, "da_remove: array is empty\n");
        return;
    }
    if (idx >= arr->size)
    {
        fprintf(stderr, "da_remove: index %zu out of bounds (size = %zu)\n", idx, arr->size);
        return;
    }
    shift_left_from(arr, idx);
    try_shrink_capacity(arr);
}


void da_remove_value(DynamicArray *arr, int value)
{
    if (!arr)
    {
        fprintf(stderr, "da_remove_value: null array pointer\n");
        return;
    }
    if (arr->size == 0)
    {
        fprintf(stderr, "da_remove_value: array is empty\n");
        return;
    }

    int idx = da_index_of(arr, value);
    if (idx == -1)
    {
        fprintf(stderr, "da_remove_value: the element %d not found in array\n", value);
        return;
    }
    shift_left_from(arr, idx);
    try_shrink_capacity(arr);
}


void da_remove_nth_value(DynamicArray *arr, int value, size_t n)
{
    if (!arr)
    {
        fprintf(stderr, "da_remove_nth_value: null array pointer\n");
        return;
    }
    if (arr->size == 0)
    {
        fprintf(stderr, "da_remove_nth_value: array is empty\n");
        return;
    }

    int idx = da_index_of_nth(arr, value, n);
    if (idx == -1)
    {
        fprintf(stderr, "da_remove_nth_value: the element %d not found in array\n", value);
        return;
    }
    shift_left_from(arr, idx);
    try_shrink_capacity(arr);
}


void da_replace(DynamicArray *arr, int old_value, int new_value)
{
    if (!arr)
    {
        fprintf(stderr, "da_replace: null array pointer\n");
        return;
    }

    int idx_old_value = da_index_of(arr, old_value);
    if (idx_old_value == -1)
    {
        fprintf(stderr, "da_replace: element %d not found in array\n", old_value);
        return;
    }
    arr->data[idx_old_value] = new_value;
}


void da_replace_nth(DynamicArray *arr, int old_value, int new_value, size_t n)
{
    if (!arr)
    {
        fprintf(stderr, "da_replace_nth: null array pointer\n");
        return;
    }

    int idx_old_value = da_index_of_nth(arr, old_value, n);
    if (idx_old_value == -1)
    {
        fprintf(stderr, "da_replace_nth: %zuth occurrence of element %d not found in array\n", n, old_value);
        return;
    }
    arr->data[idx_old_value] = new_value;
}


void da_swap(DynamicArray *arr, size_t i, size_t j)
{
    if (!arr)
    {
        fprintf(stderr, "da_swap: null array pointer\n");
        return;
    }
    if (i >= arr->size || j >= arr->size)
    {
        fprintf(stderr, "da_swap: index %zu or %zu out of bounds (size = %zu)\n", i, j, arr->size);
        return;
    }
    
    int temp;
    temp = arr->data[i];
    arr->data[i] = arr->data[j];
    arr->data[j] = temp;
}


size_t da_size(DynamicArray *arr)
{
    if (!arr)
    {
        fprintf(stderr, "da_size: null array pointer\n");
        return DA_INVALID_SIZE;
    }
    return arr->size;
}


size_t da_capacity(DynamicArray *arr)
{
    if (!arr)
    {
        fprintf(stderr, "da_capacity: null array pointer\n");
        return DA_INVALID_SIZE;
    }
    return arr->capacity;
}


int da_is_empty(DynamicArray *arr)
{
    if (!arr)
    {
        fprintf(stderr, "da_is_empty: null array pointer\n");
        return 1;
    }
    return arr->size == 0;
}


int da_equals(DynamicArray *arr1, DynamicArray *arr2)
{
    if (!arr1 || !arr2)
    {
        fprintf(stderr, "da_equals: null array pointer\n");
        return -1;
    }
    if (arr1->size != arr2->size)
        return 0;
    
    for (size_t i = 0; i < arr1->size; i++)
        if (arr1->data[i] != arr2->data[i])
            return 0;
    return 1;
}


int da_max(DynamicArray *arr)
{
    if (!arr)
    {
        fprintf(stderr, "da_max: null array pointer\n");
        return ((int)-1);
    }
    if (arr->size == 0)
    {
        fprintf(stderr, "da_max: array is empty\n");
        return ((int)-1);
    }

    int max = arr->data[0];
    for (size_t i = 1; i < arr->size; i++)
        if (arr->data[i] > max)
            max = arr->data[i];
    return max;
}

int da_min(DynamicArray *arr)
{
    if (!arr)
    {
        fprintf(stderr, "da_min: null array pointer\n");
        return ((int)-1);
    }
    if (arr->size == 0)
    {
        fprintf(stderr, "da_min: array is empty\n");
        return ((int)-1);
    }
    
    int min = arr->data[0];
    for (size_t i = 1; i < arr->size; i++)
        if (arr->data[i] < min)
            min = arr->data[i];
    return min;
}

DynamicArray *da_filter(DynamicArray *arr, int (*predicate)(int))
{
    if (!arr)
    {
        fprintf(stderr, "da_filter: null array pointer\n");
        return NULL;
    }
    if (!predicate)
    {
        fprintf(stderr, "da_filter: null predicate function\n");
        return NULL;
    }

    DynamicArray *filtered_array = da_create(MIN_CAPACITY);
    if (!filtered_array)
    {
        fprintf(stderr, "da_filter: failed to allocate memory\n");
        return NULL;
    }
    
    for (size_t i = 0; i < arr->size; i++)
        if (predicate(arr->data[i]) == 1)
            da_add_last(filtered_array, arr->data[i]);
    return filtered_array;
}


DynamicArray *da_clone(DynamicArray *arr)
{
    if (!arr)
    {
        fprintf(stderr, "da_clone: null array pointer\n");
        return NULL;
    }

    DynamicArray *clone = da_create(arr->capacity);
    if (!clone)
    {
        fprintf(stderr, "da_clone: failed to allocate memory\n");
        return NULL;
    }

    for (size_t i = 0; i < arr->size; i++)
        da_add_last(clone, arr->data[i]);
    return clone;
}


int *da_to_array(DynamicArray *arr)
{
    if (!arr)
    {
        fprintf(stderr, "da_to_array: null array pointer\n");
        return NULL;
    }

    int *array = (int *)malloc(arr->size * sizeof(int));
    if (!array)
    {

        fprintf(stderr, "da_to_array: failed to allocate memory\n");
        return NULL;
    }

    for (size_t i = 0; i < arr->size; i++)
        array[i] = arr->data[i];
    return array;
}


DynamicArray *da_slice(DynamicArray *arr, size_t start, size_t end)
{
    if (!arr)
    {
        fprintf(stderr, "da_slice: null array pointer\n");
        return NULL;
    }

    if (start > end || end >= arr->size)
    {
        fprintf(stderr, "da_slice: invalid indexes for start: %zu, end: %zu\n", start, end);
        return NULL;
    }

    DynamicArray *slice = da_create(MIN_CAPACITY);
    if (!slice)
    {
        fprintf(stderr, "da_slice: failed to allocate memory\n");
        return NULL;
    }

    for (size_t i = start; i <= end; i++)
        da_add_last(slice, arr->data[i]);
    return slice;
}


void da_foreach(DynamicArray *arr, void (*fn)(int *))
{
    if (!arr)
    {
        fprintf(stderr, "da_foreach: null array pointer\n");
        return;
    }
    if (!fn)
    {
        fprintf(stderr, "da_foreach: null fn function\n");
        return;
    }

    for (size_t i = 0; i < arr->size; i++)
        fn(&arr->data[i]);
}


void da_merge(DynamicArray *dest, DynamicArray *src)
{
    if (!dest)
    {
        fprintf(stderr, "da_merge: null array pointer\n");
        return;
    }
    if (!src)
    {
        fprintf(stderr, "da_merge: null array pointer\n");
        return;
    }

    for (size_t i = 0; i < src->size; i++)
        da_add_last(dest, src->data[i]);
}


void da_resize(DynamicArray *arr, size_t new_capacity)
{
    if (!arr)
    {
        fprintf(stderr, "da_resize: null array pointer\n");
        return;
    }

    if (new_capacity < MIN_CAPACITY)
        new_capacity = MIN_CAPACITY;

    if (new_capacity == arr->capacity)
        return;

    int *temp_data = (int *)realloc(arr->data, new_capacity * sizeof(int));
    if (temp_data)
    {
        arr->data = temp_data;
        arr->capacity = new_capacity;
    }
    else
        fprintf(stderr, "da_resize: failed resize the capacity\n");
}


void da_reverse(DynamicArray *arr)
{
    if (!arr)
    {
        fprintf(stderr, "da_reverse: null array pointer\n");
        return;
    }

    for (size_t i = 0; i < arr->size / 2; i++)
        da_swap(arr, i, arr->size - i - 1);
}


void da_clear(DynamicArray *arr)
{
    if (!arr)
    {
        fprintf(stderr, "da_clear: null array pointer\n");
        return;
    }
    arr->size = 0;
    try_shrink_capacity(arr);
}


void da_fill(DynamicArray *arr, int value)
{
    if (!arr)
    {
        fprintf(stderr, "da_fill: null array pointer\n");
        return;
    }

    for (size_t i = 0; i < arr->size; i++)
        arr->data[i] = value;
}


static int ascending_compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}


static int descending_compare(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}


void da_sort(DynamicArray *arr, SortOrder order)
{
    if (!arr)
    {
        fprintf(stderr, "da_sort: null array pointer\n");
        return;
    }

    int (*cmp)(const void *, const void *) = NULL;
    if (order == ASCENDING)
        cmp = ascending_compare;
    else if (order == DESCENDING)
        cmp = descending_compare;
    else
    {
        fprintf(stderr, "da_sort: unknown sort order\n");
        return;
    }
    qsort(arr->data, arr->size, sizeof(int), cmp);
}
