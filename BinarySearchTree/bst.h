#ifndef BST_H
#define BST_H

#include <stddef.h>

typedef struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

typedef struct
{
    Node *root;
    size_t size;
} BST;

BST *bst_create();
void bst_destroy(BST *bst);

int bst_insert(const BST *bst, int value);
int bst_remove(const BST *bst, int value);

Node *bst_search(const BST *bst, int value); // Search for a value in the BST. Returns a pointer to the node if found, otherwise NULL.
int bst_contains(const BST *bst, int value); // Return 1 if the value exists in the BST, 0 otherwise.

int bst_min(const BST *bst);
int bst_max(const BST *bst);

/*
    Return a dynamically allocated array of all elements in the BST.
    - Inorder:    Left → Root → Right
    - Preorder:   Root → Left → Right
    - Postorder:  Left → Right → Root
    The array has bst_size(bst) elements. Caller must free the returned array.
*/
int *bst_inorder_traverse(const BST *bst);
int *bst_preorder_traverse(const BST *bst);
int *bst_postorder_traverse(const BST *bst);

size_t bst_size(const BST *bst);
int bst_is_empty(const BST *bst);

#endif // BST_H