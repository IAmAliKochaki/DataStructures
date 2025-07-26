#include <stdio.h>
#include <stdlib.h>
#include "avlt.h"

AVLTree *avlt_create()
{
    AVLTree *avlt = (AVLTree *)malloc(sizeof(AVLTree));
    if (!avlt)
    {
        fprintf(stderr, "avlt_create: avl-tree creation failed.\n");
        return NULL;
    }

    avlt->root = NULL;
    avlt->size = 0;

    return avlt;
}

static void free_avlt_node(AVLTNode *node)
{
    if (!node)
        return;
    free_avlt_node(node->left);  // Free left subtree
    free_avlt_node(node->right); // Free right subtree
    free(node);                  // Free the node
}

void avlt_destroy(AVLTree *avlt)
{
    if (!avlt)
    {
        fprintf(stderr, "avlt_destroy: null pointer avl-tree.\n");
        return;
    }

    free_avlt_node(avlt->root);
    free(avlt);
}
