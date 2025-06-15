#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>
#include "LinkedList/linkedlist.h"

typedef struct
{
    linkedlist **buckets; // Array of pointers to linked lists (separate chaining)
    size_t size;
    size_t count;
} HashTable;

HashTable *ht_create(size_t initial_size); // Create a new hash table.
void ht_destroy(HashTable *hash_table);    // Free the memory used by the hash table.

int ht_add(HashTable *hash_table, int value);     // Adds a value to the table (returns 1 on success, 0 on failure).
void ht_remove(HashTable *hash_table, int value); // Removes a value.

int ht_is_empty(HashTable *hash_table); // Return 1 if the hash table is empty, 0 otherwise
int ht_size(HashTable *hash_table);     // Return the current number of elements in the hash table.

int ht_contains(HashTable *hash_table, int value); // Check if a value exists in the table.

#endif // HASH_TABLE_H
