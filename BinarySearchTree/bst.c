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

static Node *create_node(int value)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
        return NULL;

    new_node->key = value;
    new_node->left = new_node->right = new_node->parent = NULL;

    return new_node;
}

static int insert_to_bst(Node *node, Node *new_node)
{
    if (new_node->key < node->key) // go to the left subtree
    {
        if (node->left == NULL)
        {
            node->left = new_node;
            new_node->parent = node;
            return 1;
        }
        insert_to_bst(node->left, new_node);
    }

    if (new_node->key > node->key) // go to the right subtree
    {
        if (node->right == NULL)
        {
            node->right = new_node;
            new_node->parent = node;
            return 1;
        }
        insert_to_bst(node->right, new_node);
    }

    return 0;
}

int bst_insert(BST *bst, int value)
{
    if (!bst)
    {
        fprintf(stderr, "bst_insert: null pointer binary search tree.\n");
        return 0;
    }

    Node *new_node = create_node(value);
    if (!new_node)
    {
        fprintf(stderr, "bst_insert: insert new value failed because allocation.\n");
        return 0;
    }

    if (bst->root == NULL)
        bst->root = new_node;
    else if (insert_to_bst(bst->root, new_node) == 0)
    {
        fprintf(stderr, "bst_insert: insert new value failed because duplication.\n");
        return 0;
    }
    bst->size++;
    return 1;
}

static Node *min_node(const Node *node)
{
    while (node->left)
        node = node->left;
    return node;
}

static Node *max_node(const Node *node)
{
    while (node->right)
        node = node->right;
    return node;
}

static Node *find_node_by_value(Node *root, int value)
{
    if (!root)
        return NULL;
    if (value == root->key)
        return root;
    if (value < root->key)
        return find_node_by_value(root->left, value);
    return find_node_by_value(root->right, value);
}

Node *predecessor(const BST *bst, int value)
{
    if (!bst)
    {
        fprintf(stderr, "bst_predecessor: null pointer binary search tree.\n");
        return NULL;
    }

    Node *node = find_node_by_value(bst->root, value);
    if (!node)
    {
        fprintf(stderr, "bst_predecessor: %d not exists.\n", value);
        return NULL;
    }

    if (node->left)
        return max_node(node->left);

    Node *node_parent = node->parent;
    while (node_parent && node == node_parent->left)
    {
        node = node_parent;
        node_parent = node_parent->parent;
    }
    return node_parent;
}

Node *successor(const BST *bst, int value)
{

    if (!bst)
    {
        fprintf(stderr, "bst_successor: null pointer binary search tree.\n");
        return NULL;
    }

    Node *node = find_node_by_value(bst->root, value);
    if (!node)
    {
        fprintf(stderr, "bst_successor: %d not exists.\n", value);
        return NULL;
    }

    if (node->right)
        return min_node(node->right);

    Node *node_parent = node->parent;
    while (node_parent && node == node_parent->right)
    {
        node = node_parent;
        node_parent = node_parent->parent;
    }
    return node_parent;
}
