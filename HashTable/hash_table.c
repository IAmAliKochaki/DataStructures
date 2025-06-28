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

static int hash_function(int value, int size)
{
    return (value >= 0 ? value : -value) % size;
}

// Adds a value to the table (returns 1 on success, 0 on failure).
int ht_add(HashTable *hash_table, int value)
{
    if (!hash_table)
    {
        fprintf(stderr, "ht_add: null pointer hash table.\n");
        return 0;
    }

    if (hash_table->count >= hash_table->size)
    {
        fprintf(stderr, "ht_add: hash table is full.\n");
        return 0;
    }

    int add_idx = hash_function(value, hash_table->size);
    if (!hash_table->buckets[add_idx])
    {
        hash_table->buckets[add_idx] = ll_create();
        if (!hash_table->buckets[add_idx])
        {
            fprintf(stderr, "ht_add: adding failed.\n");
            return 0;
        }
    }
    if (ll_contains(hash_table->buckets[add_idx], value))
    {
        fprintf(stderr, "ht_add: %d already exists.\n", value);
        return 0;
    }
    ll_add_last(hash_table->buckets[add_idx], value);
    hash_table->count++;
    return 1;
}
void ht_remove(HashTable *hash_table, int value)
{
    if (!hash_table)
    {
        fprintf(stderr, "ht_remove: null pointer hash table.\n");
        return;
    }

    if (hash_table->count == 0)
    {
        fprintf(stderr, "ht_remove: hash table is empty.\n");
        return;
    }

    int idx = hash_function(value, hash_table->size);
    if (!hash_table->buckets[idx])
    {
        fprintf(stderr, "ht_remove: %d not exists.\n", value);
        return;
    }
    int index_in_ll = ll_index_of(hash_table->buckets[idx], value);
    if (index_in_ll == -1)
    {
        fprintf(stderr, "ht_remove: %d not exists.\n", value);
        return;
    }
    ll_remove(hash_table->buckets[idx], index_in_ll);
    hash_table->count--;
}

int ht_is_empty(HashTable *hash_table)
{
    if (!hash_table)
    {
        fprintf(stderr, "ht_is_empty: null pointer hash table.\n");
        return 1;
    }

    return hash_table->count == 0;
}

int ht_size(HashTable *hash_table)
{
    if (!hash_table)
    {
        fprintf(stderr, "ht_size: null pointer hash table.\n");
        return 0;
    }

    return hash_table->count;
}

int ht_contains(HashTable *hash_table, int value)
{
    if (!hash_table)
    {
        fprintf(stderr, "ht_contains: null pointer hash table.\n");
        return 0;
    }

    if (hash_table->count == 0)
    {
        fprintf(stderr, "ht_contains: hash table is empty.\n");
        return 0;
    }

    int idx = hash_function(value, hash_table->size);
    if (!hash_table->buckets[idx])
        return 0;

    int index_in_ll = ll_index_of(hash_table->buckets[idx], value);

    return index_in_ll == -1 ? 0 : 1;
}