#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList/linkedlist.h"

typedef struct
{
    linkedlist *list;
} Queue;

Queue *q_create();            // Create a new queue.
void q_destroy(Queue *queue); // Free the memory used by the queue.

void enqueue(Queue *queue, int value); // Enter an integer value onto the queue.
int dequeue(Queue *queue);             // Removes and returns the first element from the queue.

int q_is_empty(Queue *queue); // Return 1 if the queue is empty, 0 otherwise.
int q_size(Queue *queue);     // Return the current number of elements in the queue.

#endif // QUEUE_H