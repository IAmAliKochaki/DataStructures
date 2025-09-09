# Hash Table (Separate Chaining with Linked Lists) in C

This project implements a **Hash Table** data structure in C using **separate chaining** with linked lists to handle collisions. It supports basic operations like adding, removing, and checking for the existence of elements, while keeping the implementation clean and modular for educational purposes.

## ✅ Features

- Create and destroy a hash table
- Add and remove integer elements
- Check if a value exists in the table
- Check if the table is empty
- Get the current number of elements
- Graceful error handling for null pointers and duplicates

## 🔧 API Overview

```c
HashTable *ht_create(size_t initial_size);
void ht_destroy(HashTable *hash_table);

int ht_add(HashTable *hash_table, int value);
void ht_remove(HashTable *hash_table, int value);

int ht_is_empty(HashTable *hash_table);
int ht_size(HashTable *hash_table);
int ht_contains(HashTable *hash_table, int value);
```
For full definitions and descriptions, see hash_table.h.

## 🚀 Getting Started

Clone the repository:

    git clone https://github.com/IAmAliKochaki/DataStructures.git
    cd HashTable

Compile:

    gcc -I../ use.c hash_table.c ../LinkedList/linkedlist.c

Run:

    ./a.out

Replace use.c with your own test file if needed.

## 🛠️ Requirements

    GCC or Clang

    Standard C Library

## 🧪 Testing

You can write your own use.c to test the features, use.c is a quick example.