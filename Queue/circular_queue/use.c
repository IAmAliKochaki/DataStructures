#include <stdio.h>
#include "cqueue.h"

int main(void)
{    
    CQueue *cqueue = cq_create(5);
    if (!cqueue)
        return 1;

    enqueue(NULL, 2);

    dequeue(cqueue);
    
    enqueue(cqueue, 1);
    enqueue(cqueue, 2);
    
    printf("queue size: %d", cq_size(cqueue));
    
    enqueue(cqueue, 3);
    enqueue(cqueue, 4);
    enqueue(cqueue, 5);
    
    printf("%d\n", dequeue(cqueue));
    
    enqueue(cqueue, 6);
    enqueue(cqueue, 7);

    while (!cq_is_empty(cqueue))
        printf("%d\n", dequeue(cqueue));

    dequeue(cqueue);

    cq_destroy(cqueue);
}