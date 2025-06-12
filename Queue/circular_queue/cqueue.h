#ifndef CQUEUE_H
#define CQUEUE_H

#include <stddef.h>

typedef struct
{
    int *array;
    size_t capacity;
    size_t front;
    size_t rear;
    size_t size;
} CQueue;

CQueue *cq_create(size_t capacity); // Create a new circular queue.
void cq_destroy(CQueue *cqueue);    // Free the memory used by the queue.

void enqueue(CQueue *cqueue, int value); // Enter an integer value onto the queue.
int dequeue(CQueue *cqueue);             // Removes and returns the first element from the queue.

int cq_is_empty(CQueue *cqueue); // Return 1 if the queue is empty, 0 otherwise.
int cq_is_full(CQueue *cqueue);  // Return 1 if the queue is full, 0 otherwise.
int cq_size(CQueue *cqueue);      // Return the current number of elements in the queue.

#endif // CQUEUE_H