#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main(void)
{
    BST *bst = bst_create();
    if (!bst)
    {
        printf("Binary search tree creation failed.\n");
        return 1;
    }

    if (bst_insert(bst, 30) == 0)
        printf("insertion 30 failed.\n");
    else
        printf("insertion 30 successful.\n");

    if (bst_insert(bst, 69) == 0)
        printf("insertion 69 failed.\n");
    else
        printf("insertion 69 successful.\n");

    if (bst_insert(bst, 11) == 0)
        printf("insertion 11 failed.\n");
    else
        printf("insertion 11 successful.\n");

    if (bst_insert(bst, 4) == 0)
        printf("insertion 4 failed.\n");
    else
        printf("insertion 4 successful.\n");

    // insert with duplication
    if (bst_insert(bst, 4) == 0)
        printf("insertion 4 failed.\n");
    else
        printf("insertion 4 successful.\n");
    
    Node *node = bst_search(bst, 11);

    if (!node)
        printf("%d not found.\n", 11);
    
    bst_remove(bst, 11);
    if (bst_contains(bst, 11) == 0)
        printf("%d not found.\n", 11);

    int min = bst_min(bst);
    printf("min: %d", min);

    int *inorder_traverse = bst_inorder_traverse(bst);
    if (inorder_traverse)
    {
        for (int i = 0; i < bst_size(bst); i++)
            printf("[%d]: %d\n", i, inorder_traverse[i]);
        free(inorder_traverse);
    }

    bst_destroy(bst);
    return 0;
}   