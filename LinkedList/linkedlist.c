#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"


// Create a new linked list.
linkedlist *ll_create()
{
    linkedlist *new_ll = (linkedlist *)malloc(sizeof(linkedlist));
    if (!new_ll)
    {
        fprintf(stderr, "ll_create: linked list creation is failed.\n");
        return NULL;
    }
    new_ll->head = new_ll->tail = NULL;
    new_ll->size = 0;
    return new_ll;
}

// Free all memory used by linked list.
void ll_destroy(linkedlist *ll)
{
    if (!ll)
    {
        fprintf(stderr, "ll_destroy: null linked list pointer\n");
        return;
    }

    Node *current_node, *next_node;
    current_node = ll->head;
    while (current_node)
    {
        next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    free(ll);
}
