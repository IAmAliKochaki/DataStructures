#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "linkedlist.h"


#define LL_ERROR_VALUE INT_MIN


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

void ll_remove_first(linkedlist *ll)
{
    if (!ll)
    {
        fprintf(stderr, "ll_remove_first: null linked list pointer\n");
        return;
    }

    if (ll->size == 0)
    {
        fprintf(stderr, "ll_remove_first: linked list is empty.\n");
        return;
    }

    Node *tmp = ll->head;
    ll->head = ll->head->next;
    if (ll->size == 1)
        ll->tail = NULL;
    ll->size--;
    free(tmp);
}

void ll_remove_last(linkedlist *ll)
{
    if (!ll)
    {
        fprintf(stderr, "ll_remove_last: null linked list pointer\n");
        return;
    }

    if (ll->size == 0)
    {
        fprintf(stderr, "ll_remove_last: linked list is empty.\n");
        return;
    }

    if (ll->size == 1)
    {
        free(ll->head);
        ll->head = ll->tail = NULL;
        ll->size = 0;
        return;
    }

    Node *current = ll->head;
    while (current->next != ll->tail)
        current = current->next;

    free(ll->tail);
    ll->tail = current;
    ll->tail->next = NULL;
    ll->size--;
}

void ll_remove(linkedlist *ll, size_t idx)
{
    if (!ll)
    {
        fprintf(stderr, "ll_remove: null linked list pointer\n");
        return;
    }

    if (ll->size == 0)
    {
        fprintf(stderr, "ll_remove: linked list is empty.\n");
        return;
    }

    if (idx >= ll->size)
    {
        fprintf(stderr, "ll_remove: index out of bounds.\n");
        return;
    }

    if (idx == 0)
    {
        ll_remove_first(ll);
        return;
    }

    if (idx == ll->size - 1)
    {
        ll_remove_last(ll);
        return;
    }

    Node *current = ll->head;
    for (size_t i = 0; i < idx - 1; i++)
        current = current->next;

    Node *tmp = current->next;
    current->next = current->next->next;
    ll->size--;
    free(tmp);
}

int ll_get(linkedlist *ll, size_t idx)
{
    if (!ll)
    {
        fprintf(stderr, "ll_get: null linked list pointer\n");
        return LL_ERROR_VALUE;
    }

    if (ll->size == 0)
    {
        fprintf(stderr, "ll_get: linked list is empty.\n");
        return LL_ERROR_VALUE;
    }
    
    if (idx >= ll->size)
    {
        fprintf(stderr, "ll_get: index out of bounds.\n");
        return LL_ERROR_VALUE;
    }
    
    Node *current = ll->head;
    for (size_t i = 0; i < idx; i++)
        current = current->next;
    
    return current->data;
}

void ll_set(linkedlist *ll, size_t idx, int value)
{
    if (!ll)
    {
        fprintf(stderr, "ll_set: null linked list pointer\n");
        return;
    }

    if (ll->size == 0)
    {
        fprintf(stderr, "ll_set: linked list is empty.\n");
        return;
    }
    
    if (idx >= ll->size)
    {
        fprintf(stderr, "ll_set: index out of bounds.\n");
        return;
    }
    
    Node *current = ll->head;
    for (size_t i = 0; i < idx; i++)
        current = current->next;
    
    current->data = value;
}

int ll_contains(linkedlist *ll, int value)
{
    if (!ll)
    {
        fprintf(stderr, "ll_contains: null linked list pointer\n");
        return 0;
    }

    Node *node = ll->head;
    while (node)
    {
        if (node->data == value)
            return 1;
        node = node->next;
    }

    return 0;
}
int ll_index_of(linkedlist *ll, int value)
{
    if (!ll)
    {
        fprintf(stderr, "ll_index_of: null linked list pointer\n");
        return -1;
    }

    Node *node = ll->head;
    int i = 0;
    while (node)
    {
        if (node->data == value)
            return i;
        node = node->next;
        i++;
    }

    return -1;
}

int ll_index_of_nth(linkedlist *ll, int value, size_t n)
{

    if (!ll)
    {
        fprintf(stderr, "ll_index_of_nth: null linked list pointer\n");
        return -1;
    }

    Node *node = ll->head;
    int i = 0, nth = 1;
    while (node)
    {
        if (node->data == value && nth++ == n)
            return i;
        node = node->next;
        i++;
    }

    return -1;
}

// Properties
size_t ll_size(linkedlist *ll)
{
    if (!ll)
    {
        fprintf(stderr, "ll_size: null linked list pointer\n");
        return (size_t) - 1;
    }

    return ll->size;
}
int ll_is_empty(linkedlist *ll)
{
    if (!ll)
    {
        fprintf(stderr, "ll_is_empty: null linked list pointer\n");
        return -1;
    }

    return ll->size == 0;
}
