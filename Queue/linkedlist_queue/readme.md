# Queue (Linked List-Based) in C

This project implements a **Queue** data structure using a **singly linked list** in C. It follows the classic FIFO (First-In, First-Out) behavior and provides a simple API for queue operations.

## ✅ Features

- Create and destroy a queue
- Enqueue (add) elements to the back of the queue
- Dequeue (remove) elements from the front of the queue
- Check if the queue is empty
- Get the current size of the queue
- Graceful error handling for null pointers and empty queue cases

## 🔧 API Overview

```c
Queue *q_create();
void q_destroy(Queue *queue);
void enqueue(Queue *queue, int value);
int dequeue(Queue *queue);
int q_is_empty(Queue *queue);
int q_size(Queue *queue);
```
For full definitions and descriptions, see queue.h.

## 🚀 Getting Started

Clone the repository:

    git clone https://github.com/IAmAliKochaki/DataStructures.git
    cd Queue/linkedlist_queue 

Compile:

    gcc -I../.. queue.c use.c ../../LinkedList/linkedlist.c

Run:

    ./a.out

Replace use.c with your own test file if needed.

## 🛠️ Requirements

    GCC or Clang

    Standard C library

## 🧪 Testing

You can write your own use.c to test the features, use.c is a quick example.
