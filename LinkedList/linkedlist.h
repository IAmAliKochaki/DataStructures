#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stddef.h>

/*
 * Struct representing a node in a singly linked list.
 * Using int for simplicity; can be adapted for other types.
 */
typedef struct
{
    int data;
    Node *next;
} Node;

// Struct representing a singly linked list.
typedef struct
{
    Node *head;
    Node *tail;
    size_t size;
} linkedlist;

// Creation and Destruction
linkedlist *ll_create(); // Create a new linked list.
void ll_destroy(linkedlist *ll); // Free all memory used by linked list.

// Adding
void ll_add_first(linkedlist *ll, int value); // Add a value to the beginning of the list. 
void ll_add_last(linkedlist *ll, int value); // Add a value to the end of the list.
void ll_add(linkedlist *ll, int value, size_t idx); // Add a value to the specified index. 

// Removing
void ll_remove_first(linkedlist *ll); // Remove the first element of the list.
void ll_remove_last(linkedlist *ll); // Remove the last element of the list.
void ll_remove(linkedlist *ll, size_t idx); // Remove the element at the specified index.

// Access and Modification
int ll_get(linkedlist *ll, size_t idx); // Return the value at the specified index.
void ll_set(linkedlist *ll, size_t idx, int value); // Set the value at the specified index.

// Searching
int ll_contains(linkedlist *ll, int value); // Return 1 if the list contains the value, 0 otherwise.
int ll_index_of(linkedlist *ll, size_t idx); // Return the index of the first occurrence of the value, or -1 if not found.
int ll_index_of_nth(linkedlist *ll, size_t idx, size_t n); // Return the index of the nth occurrence of the value, or -1 if not found.

// Properties
size_t ll_size(linkedlist *ll); // Return the current number of elements in the list.
int ll_is_empty(linkedlist *ll); // Return 1 if the list is empty, 0 otherwise.

#endif // LINKEDLIST_H
