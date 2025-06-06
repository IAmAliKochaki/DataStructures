# Linked List in C

This project implements a **singly linked list** data structure in C, designed with clarity, modularity, andd error handling in mind. It supports basic list operations such as adding, removing, accessing and searching elements.


## ✅ Features

- Create and destroy linked lists
- Add elements at:
  - The beginning (`ll_add_first`)
  - The end (`ll_add_last`)
  - A specific index (`ll_add`)
- Remove elements from:
  - The beginning (`ll_remove_first`)
  - The end (`ll_remove_last`)
  - A specific index (`ll_remove`)
- Access and modify elements:
  - Get element by index (`ll_get`)
  - Set element at index (`ll_set`)
- Search:
  - Check if list contains value (`ll_contains`)
  - Get index of first occurrence (`ll_index_of`)
  - Get index of Nth occurrence (`ll_index_of_nth`)
- Properties:
  - Get current size (`ll_size`)
  - Check if list is empty (`ll_is_empty`)


## 🚀 Getting Started

Clone the repository:

    git clone https://github.com/IAmAliKochaki/DataStructures.git
    cd LinkedList

Compile:

    gcc linkedlist.c use.c

Run:

    ./a.out

Replace use.c with your test file containing function calls for testing the API.

## 🛠️ Requirements

    GCC or Clang

    Standard C library


## 🧪 Testing

You can write your own use.c to test the features, use.c is a quick example.