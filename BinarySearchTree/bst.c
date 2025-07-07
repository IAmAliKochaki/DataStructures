#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

BST *bst_create()
{
    BST *new_bst = (BST *)malloc(sizeof(BST));
    if (!new_bst)
    {
        fprintf(stderr, "bst_create: binary search tree creation failed.\n");
        return NULL;
    }

    new_bst->root = NULL;
    new_bst->size = 0;

    return new_bst;
}

static void free_tree_nodes(Node *node)
{
    if (!node)
        return;
    free_tree_nodes(node->left);  // Free left subtree
    free_tree_nodes(node->right); // Free right subtree
    free(node);                   // Free the node
}

void bst_destroy(BST *bst)
{
    if (!bst)
    {
        fprintf(stderr, "bst_destroy: null pointer binary search tree.\n");
        return;
    }

    free_tree_nodes(bst->root);
    free(bst);
}
