# Queue (Circular Array-Based) in C

This project implements a **Queue** data structure using a **circular array** in C. It follows the FIFO (First-In, First-Out) principle while efficiently utilizing the array space by wrapping around when the end is reached.

## ✅ Features

- Create and destroy a circular queue
- Enqueue (add) elements to the rear
- Dequeue (remove) elements from the front
- Check if the queue is empty or full
- Get the current size of the queue
- Graceful error handling for null pointers, empty, and full queue cases

## 🔧 API Overview

```c
CQueue *cq_create(size_t capacity);
void cq_destroy(CQueue *cqueue);
void enqueue(CQueue *cqueue, int value);
int dequeue(CQueue *cqueue);
int cq_is_empty(CQueue *cqueue);
int cq_is_full(CQueue *cqueue);
int cq_size(CQueue *cqueue);
```
For full definitions and descriptions, see cqueue.h.

## 🚀 Getting Started

Clone the repository:

    git clone https://github.com/IAmAliKochaki/DataStructures.git
    cd Queue/circular_queue

Compile:

    gcc cqueue.c use.c

Run:

    ./a.out

Replace use.c with your own test file if needed.

## 🛠️ Requirements

    GCC or Clang

    Standard C library

## 🧪 Testing
You can write your own use.c to test the features, use.c is a quick example.
