#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "cqueue.h"

#define CQ_ERROR_VALUE INT_MIN

CQueue *cq_create(size_t capacity)
{
    CQueue *new_cqueue = (CQueue *)malloc(sizeof(CQueue));
    if (!new_cqueue)
    {
        fprintf(stderr, "cq_create: queue creation failed.\n");
        return NULL;
    }

    new_cqueue->array = (int *)malloc(capacity * sizeof(int));
    if (!new_cqueue->array)
    {
        fprintf(stderr, "cq_create: queue creation failed.\n");
        free(new_cqueue);
        return NULL;
    }

    new_cqueue->front = new_cqueue->rear = 0;
    new_cqueue->size = 0;
    new_cqueue->capacity = capacity;
    return new_cqueue;
}

void cq_destroy(CQueue *cqueue)
{
    if (!cqueue)
    {
        fprintf(stderr, "cq_destroy: null pointer queue.\n");
        return;
    }

    free(cqueue->array);
    free(cqueue);
}

void enqueue(CQueue *cqueue, int value)
{
    if (!cqueue)
    {
        fprintf(stderr, "enqueue: null pointer queue.\n");
        return;
    }

    if (cqueue->size == cqueue->capacity)
    {
        fprintf(stderr, "enqueue: queue is full.\n");
        return;
    }

    cqueue->array[cqueue->rear] = value;
    cqueue->rear = (cqueue->rear + 1) % cqueue->capacity;
    cqueue->size++;
}
int dequeue(CQueue *cqueue)
{
    if (!cqueue)
    {
        fprintf(stderr, "dequeue: null pointer queue.\n");
        return CQ_ERROR_VALUE;
    }

    if (cqueue->size == 0)
    {
        fprintf(stderr, "dequeue: queue is empty.\n");
        return CQ_ERROR_VALUE;
    }

    int dequeue_value = cqueue->array[cqueue->front];
    cqueue->front = (cqueue->front + 1) % cqueue->capacity;
    cqueue->size--;
    return dequeue_value;
}
int cq_is_empty(CQueue *cqueue)
{
    if (!cqueue)
    {
        fprintf(stderr, "cq_is_empty: null pointer queue.\n");
        return 1;
    }
    return cqueue->size == 0;
}

int cq_is_full(CQueue *cqueue)
{
    if (!cqueue)
    {
        fprintf(stderr, "cq_is_full: null pointer queue.\n");
        return 1;
    }
    return cqueue->size == cqueue->capacity;
}

int cq_size(CQueue *cqueue)
{
    if (!cqueue)
    {
        fprintf(stderr, "cq_size: null pointer queue.\n");
        return 0;
    }
    return cqueue->size;
}
