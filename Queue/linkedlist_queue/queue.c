#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "queue.h"

#define Q_ERROR_VALUE INT_MIN

Queue *q_create()
{
    Queue *new_queue = (Queue *)malloc(sizeof(Queue));
    if (!new_queue)
    {
        fprintf(stderr, "q_create: queue creation failed.\n");
        return NULL;
    }

    new_queue->list = ll_create();
    if (!new_queue->list)
    {
        fprintf(stderr, "q_create: queue creation failed.\n");
        free(new_queue);
        return NULL;
    }

    return new_queue;
}

void q_destroy(Queue *queue)
{
    if (!queue)
    {
        fprintf(stderr, "q_destroy: null pointer queue.\n");
        return;
    }

    ll_destroy(queue->list);
    free(queue);
}

void enqueue(Queue *queue, int value)
{
    if (!queue)
    {
        fprintf(stderr, "enqueue: null pointer queue.\n");
        return;
    }

    ll_add_last(queue->list, value);
}

int dequeue(Queue *queue)
{
    if (!queue)
    {
        fprintf(stderr, "dequeue: null pointer queue.\n");
        return Q_ERROR_VALUE;
    }

    if (ll_is_empty(queue->list))
    {
        fprintf(stderr, "dequeue: queue is empty.\n");
        return Q_ERROR_VALUE;
    }

    int dequeue_value = ll_get(queue->list, 0);
    ll_remove_first(queue->list);
    return dequeue_value;
}

int q_is_empty(Queue *queue)
{
    if (!queue)
    {
        fprintf(stderr, "q_is_empty: null pointer queue.\n");
        return 1;
    }

    return ll_is_empty(queue->list);
}

int q_size(Queue *queue)
{
    if (!queue)
    {
        fprintf(stderr, "q_size: null pointer queue.\n");
        return 0;
    }

    return ll_size(queue->list);
}