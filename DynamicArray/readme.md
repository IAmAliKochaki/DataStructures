# Dynamic Array in C

This project implements a **Dynamic Array** in C, similar to high-level dynamic containers like `std::vector` in C++. It supports a wide range of operations including insertion, deletion, searching, resizing, filtering, sorting, and more.


## ✅ Features

- Create and destroy dynamic arrays
- Add/remove elements at the beginning or end
- Get/set values by index
- Search (index of, contains, count, etc.)
- Remove by value or index (including nth occurrence)
- Replace and swap elements
- Check properties (size, capacity, isEmpty, equals, max, min)
- Clone, filter, slice, convert to array
- Iterate using `foreach`
- Merge, clear, fill, sort, and reverse

## 🔧 API Overview

```c
DynamicArray *da_create(size_t initial_capacity);
void da_destroy(DynamicArray *arr);
int da_get(DynamicArray *arr, size_t idx);
void da_set(DynamicArray *arr, size_t idx, int value);
void da_add_first(DynamicArray *arr, int value);
void da_add_last(DynamicArray *arr, int value);
void da_remove_first(DynamicArray *arr);
void da_remove_last(DynamicArray *arr);
void da_remove(DynamicArray *arr, size_t idx);
// ... and many more!
```
For a complete list of functions, see dynamic_array.h

## 🚀 Getting Started

Clone the repository:

    git clone https://github.com/yourusername/dynamic-array-c.git
    cd DynamicArray

Compile:

    gcc dynamic_array.c use.c

Run:

    ./a.out

Replace use.c with your test file containing function calls for testing the API.

## 🛠️ Requirements

    GCC or Clang

    Standard C library


## 🧪 Testing

You can write your own use.c to test the features, use.c is a quick example.