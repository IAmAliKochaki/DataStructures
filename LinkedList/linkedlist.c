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

// Adding
// Add a value to the beginning of the list.

static Node *create_node(int value)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
        return NULL;
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void ll_add_first(linkedlist *ll, int value)
{
    if (!ll)
    {
        fprintf(stderr, "ll_add_first: null linked list pointer\n");
        return;
    }

    Node *new_node = create_node(value);
    if (!new_node)
    {
        fprintf(stderr, "ll_add_first: node creation failed.\n");
        return;
    }
    new_node->next = ll->head;
    ll->head = new_node;
    if (ll->size == 0)
        ll->tail = new_node;
    ll->size++;
}

// Add a value to the end of the list.
void ll_add_last(linkedlist *ll, int value)
{
    if (!ll)
    {
        fprintf(stderr, "ll_add_last: null linked list pointer\n");
        return;
    }

    Node *new_node = create_node(value);
    if (!new_node)
    {
        fprintf(stderr, "ll_add_last: node creation failed.\n");
        return;
    }

    if (!ll->head)
    {
        ll->head = new_node;
        ll->tail = new_node;
        ll->size++;
        return;
    }

    ll->tail->next = new_node;
    ll->tail = new_node;
    ll->size++;
}

// Add a value to the specified index.
void ll_add(linkedlist *ll, int value, size_t idx)
{
    if (!ll)
    {
        fprintf(stderr, "ll_add: null linked list pointer\n");
        return;
    }

    Node *new_node = create_node(value);
    if (!new_node)
    {
        fprintf(stderr, "ll_add: node creation failed.\n");
        return;
    }

    if (!ll->head)
    {
        // add first
        ll->head = new_node;
        ll->tail = new_node;
        ll->size++;
        return;
    }

    if (idx >= ll->size)
    {
        // add last
        ll->tail->next = new_node;
        ll->tail = new_node;
        ll->size++;
        return;
    }

    Node *current = ll->head;
    idx--;
    while (idx--)
        current = current->next;
    new_node->next = current->next;
    current->next = new_node;
    ll->size++;
}
