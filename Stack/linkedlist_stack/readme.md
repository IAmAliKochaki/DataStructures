# Stack (Linked List-Based) in C

This project implements a **Stack** data structure using a **singly linked list** in C. It mimics classic LIFO (Last-In, First-Out) behavior and provides an intuitive API for stack operations.

## ✅ Features

- Create and destroy a stack
- Push elements onto the stack
- Pop elements from the stack
- Peek at the top element without removing it
- Check if the stack is empty
- Get the current size of the stack
- Graceful error handling for null pointers and empty stack cases

## 🔧 API Overview

```c
Stack *st_create();
void st_destroy(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
int peek(Stack *stack);
int st_is_empty(Stack *stack);
int st_size(Stack *stack);
```
For full definitions and descriptions, see stack.h.

## 🚀 Getting Started

Clone the repository:

    git clone https://github.com/IAmAliKochaki/DataStructures.git
    cd Stack/linkedlist_stack

Compile:

    gcc -I../..  stack.c use.c ../../LinkedList/linkedlist.c

Run:

    ./a.out

Replace use.c with your own test file if needed.

## 🛠️ Requirements

    GCC or Clang

    Standard C library

## 🧪 Testing

You can write your own use.c to test the features, use.c is a quick example.
