#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stddef.h>

/*
 * Struct representing a dynamic array of integers.
 * using int for simplicity; can be adapted for other types.
 */
typedef struct
{
    int *data;
    size_t size;
    size_t capacity;
} DynamicArray;

typedef enum {
    ASCENDING, DESCENDING
} SortOrder;

// Creation and Destruction
DynamicArray *da_create(size_t initial_capacity); // Create a new dynamic array with an initial capacity
void da_destroy(DynamicArray *arr); // Free the memory used by the dynamic array

// Access and Modification
int da_get(DynamicArray *arr, size_t idx); // Get the element at the specified index
void da_set(DynamicArray *arr, size_t idx, int value); // Set the element at the specified index

// Searching
int da_index_of(DynamicArray *arr, int value); // Return the index of the first occurrence of the value, or -1 if not found
int da_index_of_nth(DynamicArray *arr, int value, int n); // Return the index of the nth occurrence of a value, or -1 if not found
int da_contains(DynamicArray *arr, int value); // Return 1 if the array contains the value, 0 otherwise
int da_count_value(DynamicArray *arr, int value); // Return the number of times a specific value appears in the array

// Adding and Inserting
void da_add_first(DynamicArray *arr, int value); // Add a value to the beginning of the array
void da_add_last(DynamicArray *arr, int value); // Add a value to the end of the array
void da_insert(DynamicArray *arr, size_t idx, int value); // Insert a value at the specified index

// Removing
void da_remove_first(DynamicArray *arr); // Remove the first element from the array
void da_remove_last(DynamicArray *arr); // Remove the last element from the array
void da_remove(DynamicArray *arr, size_t idx); // Remove the element at the specified index
void da_remove_value(DynamicArray *arr, int value); // Remove the first occurrence of a specific value from the array 
void da_remove_nth_value(DynamicArray *arr, int value, int n);  //  Remove the nth occurrence of a specific value from the array

// Replacement and Swapping
void da_replace(DynamicArray *arr, int old_value, int new_value); // Replace the first occurrence of old_value with new_value
void da_replace_nth(DynamicArray *arr, int old_value, int new_value, int n); // Replace the nth occurrence of old_value with new_value
void da_swap(DynamicArray *arr, size_t i, size_t j); // Swap two elements by their indexes

// Properties
size_t da_size(DynamicArray *arr); // Return the current number of elements in the array
size_t da_capacity(DynamicArray *arr); // Return the total capacity of the array
int da_is_empty(DynamicArray *arr); // Return 1 if the array is empty, 0 otherwise
int da_equals(DynamicArray *arr1, DynamicArray *arr2); // Return 1 if two dynamic arrays are equal, 0 otherwise
int da_max(DynamicArray *arr); // Return the maximum value in the array
int da_min(DynamicArray *arr); // Return the minimum value in the array

// Filter, Cloning, Conversion, and Slicing
DynamicArray *da_filter(DynamicArray *arr, int (*predicate)(int)); // Return a new array with only the elements matching predicate
DynamicArray *da_clone(DynamicArray *arr); // Create and return a deep copy of the given dynamic array
int *da_to_array(DynamicArray *arr); // Return a copy of the internal data array
DynamicArray *da_slice(DynamicArray *arr, int start, int end); // Return a new array that is a slice of the original one


// Utilities
void da_foreach(DynamicArray *arr, void(*fn)(int*)); // Apply a function to each element
void da_merge(DynamicArray *dest, DynamicArray *src); // Merge another array into the current one
void da_resize(DynamicArray *arr, size_t new_capacity); // Manually resize the array's capacity
void da_reverse(DynamicArray *arr); // Reverse the elements of the array in-place
void da_clear(DynamicArray *arr); // Clear all elements from the array (keep allocated memory)
void da_fill(DynamicArray * arr, int value); // Fill all elements of the array with a specific value
void da_sort(DynamicArray *arr ,SortOrder order); // Sort the array in the specified order (ascending or descending)

#endif // DYNAMIC_ARRAY_H
