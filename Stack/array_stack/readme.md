# Stack (Array-Based) in C

This project implements a **Stack** data structure using a fixed-size array in C. It's designed to mimic the behavior of classic LIFO (Last-In, First-Out) stacks with a simple and efficient interface.

## ✅ Features

- Create and destroy a stack
- Push elements onto the stack
- Pop elements from the stack
- Peek at the top element without removing it
- Check if the stack is full or empty
- Handles edge cases gracefully (e.g. full stack, empty stack, null pointer)

## 🔧 API Overview

```c
Stack *st_create(size_t capacity);
void st_destroy(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
int peek(Stack *stack);
int st_is_empty(Stack *stack);
int st_is_full(Stack *stack);
```
For full definitions and descriptions, see stack.h.

## 🚀 Getting Started

Clone the repository:

    git clone https://github.com/IAmAliKochaki/DataStructures.git
    cd Stack

Compile:

    gcc stack.c use.c

Run:

    ./a.out

Replace use.c with your own test file if needed.

## 🛠️ Requirements

    GCC or Clang

    Standard C library

## 🧪 Testing

You can write your own use.c to test the features, use.c is a quick example.
