#ifndef AVLT_H
#define AVLT_H

typedef struct AVLTNode
{
    int key;
    AVLTNode *left;
    AVLTNode *right;
    AVLTNode *parent;
    int height; // height of the node (used for balancing)
} AVLTNode;

typedef struct
{
    AVLTNode *root;
    int size;
} AVLTree;

AVLTree *avlt_create();
void avlt_destroy(AVLTree *avlt);

int avlt_insert(AVLTree *avlt, int value); // Insert a value into the AVLTree. Return 1 on success, 0 on failure.
int avlt_remove(AVLTree *avlt, int value); // Remove a value from the AVLTree. Return 1 on success, 0 on failure.

#endif // AVLT_H