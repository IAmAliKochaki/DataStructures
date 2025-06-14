#include <stdlib.h>
#include <stdio.h>
#include "hash_table.h"

#define MIN_CAPACITY 16

HashTable *ht_create(size_t initial_size)
{
    if (initial_size < MIN_CAPACITY)
        initial_size = MIN_CAPACITY;

    HashTable *new_hash_table = (HashTable *)malloc(sizeof(HashTable));
    if (!new_hash_table)
    {
        fprintf(stderr, "ht_create: hash table creation failed.\n");
        return NULL;
    }

    new_hash_table->buckets = (linkedlist **)malloc(initial_size * sizeof(linkedlist *));
    if (!new_hash_table->buckets)
    {
        fprintf(stderr, "ht_create: hash table creation failed.\n");
        free(new_hash_table);
        return NULL;
    }

    for (int i = 0; i < initial_size; i++)
        new_hash_table->buckets[i] = NULL;

    new_hash_table->size = initial_size;
    new_hash_table->count = 0;
    return new_hash_table;
}

void ht_destroy(HashTable *hash_table)
{
    if (!hash_table)
    {
        fprintf(stderr, "ht_destroy: null pointer hash table.\n");
        return;
    }

    for (int i = 0; i < hash_table->size; i++)
        if (hash_table->buckets[i])
            ll_destroy(hash_table->buckets[i]);

    free(hash_table->buckets);
    free(hash_table);
}
