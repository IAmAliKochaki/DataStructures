#include <stdio.h>
#include "queue.h"

int main(void)
{
    Queue *queue = q_create();
    if (!queue)
        return 1;

    enqueue(queue, 20);
    enqueue(queue, 12);
    enqueue(queue, 10);
    enqueue(queue, 3);

    printf("Queue size: %d\n", q_size(queue));

    printf("\n-------------------\n\n");

    while (!q_is_empty(queue))
        printf("dequeue: %d\n", dequeue(queue));
}
