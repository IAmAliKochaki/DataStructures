#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
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
    else if (new_node->key > node->key) // go to the right subtree
    {
        if (node->right == NULL)
        {
            node->right = new_node;
            new_node->parent = node;
            return 1;
        }
        insert_to_bst(node->right, new_node);
    }
    else
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

static Node *min_node(Node *node)
{
    while (node->left)
        node = node->left;
    return node;
}

static Node *max_node(Node *node)
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

static void transplant(BST *bst, Node *old_child, Node *new_child)
{
    // old_child is root
    if (!old_child->parent)
        bst->root = new_child;
    else if (old_child == old_child->parent->left)
        old_child->parent->left = new_child;
    else
        old_child->parent->right = new_child;
    if (new_child)
        new_child->parent = old_child->parent;
}

int bst_remove(BST *bst, int value)
{
    if (!bst)
    {
        fprintf(stderr, "bst_remove: null pointer binary search tree.\n");
        return 0;
    }

    Node *node = find_node_by_value(bst->root, value);
    if (!node)
    {
        fprintf(stderr, "bst_remove: %d not exists.\n", value);
        return 0;
    }

    if (!node->left)
        transplant(bst, node, node->right);
    else if (!node->right)
        transplant(bst, node, node->left);
    else
    {
        Node *n_s_root = min_node(node->right); // n_s_root: new subtree root
        if (n_s_root->parent != node)
        {
            transplant(bst, n_s_root, n_s_root->right);
            n_s_root->right = node->right;
            node->right->parent = n_s_root;
        }
        transplant(bst, node, n_s_root);
        n_s_root->left = node->left;
        node->left->parent = n_s_root;
    }

    free(node);
    bst->size--;
    return 1;
}

Node *bst_search(const BST *bst, int value)
{
    if (!bst)
    {
        fprintf(stderr, "bst_search: null pointer binary search tree.\n");
        return NULL;
    }

    Node *current = bst->root;
    while (current)
    {
        if (value == current->key)
            return current;
        if (value < current->key)
            current = current->left;
        else
            current = current->right;
    }

    return NULL;
}

int bst_contains(const BST *bst, int value)
{
    if (!bst)
    {
        fprintf(stderr, "bst_contains: null pointer binary search tree.\n");
        return 0;
    }

    Node *current = bst->root;
    while (current)
    {
        if (value == current->key)
            return 1;
        if (value < current->key)
            current = current->left;
        else
            current = current->right;
    }

    return 0;
}

int bst_min(const BST *bst)
{
    if (!bst)
    {
        fprintf(stderr, "bst_min: null pointer binary search tree.\n");
        return INT_MAX;
    }

    return min_node(bst->root)->key;
}

int bst_max(const BST *bst)
{
    if (!bst)
    {
        fprintf(stderr, "bst_max: null pointer binary search tree.\n");
        return INT_MIN;
    }

    return max_node(bst->root)->key;
}

static void inorder_traverse(Node *root, int *list, int *adding_index)
{
    if (root)
    {
        inorder_traverse(root->left, list, adding_index);
        list[*adding_index] = root->key;
        (*adding_index)++;
        inorder_traverse(root->right, list, adding_index);
    }
}

int *bst_inorder_traverse(const BST *bst)
{
    if (!bst)
    {
        fprintf(stderr, "bst_inorder_traverse: null pointer binary search tree.\n");
        return NULL;
    }
    if (bst->size == 0)
        return NULL;

    int *traverse = (int *)malloc(sizeof(int) * bst->size);
    if (!traverse)
    {
        fprintf(stderr, "bst_inorder_traverse: memory allocation failed.\n");
        return NULL;
    }
    int index = 0;
    inorder_traverse(bst->root, traverse, &index);

    return traverse;
}

static void preorder_traverse(Node *root, int *list, int *adding_index)
{
    if (root)
    {
        list[*adding_index] = root->key;
        (*adding_index)++;
        preorder_traverse(root->left, list, adding_index);
        preorder_traverse(root->right, list, adding_index);
    }
}

int *bst_preorder_traverse(const BST *bst)
{
    if (!bst)
    {
        fprintf(stderr, "bst_preorder_traverse: null pointer binary search tree.\n");
        return NULL;
    }
    if (bst->size == 0)
        return NULL;

    int *traverse = (int *)malloc(sizeof(int) * bst->size);
    if (!traverse)
    {
        fprintf(stderr, "bst_preorder_traverse: memory allocation failed.\n");
        return NULL;
    }
    int index = 0;
    preorder_traverse(bst->root, traverse, &index);

    return traverse;
}

static void postorder_traverse(Node *root, int *list, int *adding_index)
{
    if (root)
    {
        postorder_traverse(root->left, list, adding_index);
        postorder_traverse(root->right, list, adding_index);
        list[*adding_index] = root->key;
        (*adding_index)++;
    }
}

int *bst_postorder_traverse(const BST *bst)
{
    if (!bst)
    {
        fprintf(stderr, "bst_postorder_traverse: null pointer binary search tree.\n");
        return NULL;
    }
    if (bst->size == 0)
        return NULL;

    int *traverse = (int *)malloc(sizeof(int) * bst->size);
    if (!traverse)
    {
        fprintf(stderr, "bst_postorder_traverse: memory allocation failed.\n");
        return NULL;
    }
    int index = 0;
    postorder_traverse(bst->root, traverse, &index);

    return traverse;
}

size_t bst_size(const BST *bst)
{
    if (!bst)
    {
        fprintf(stderr, "bst_size: null pointer binary search tree.\n");
        return 0;
    }

    return bst->size;
}

int bst_is_empty(const BST *bst)
{
    if (!bst)
    {
        fprintf(stderr, "bst_is_empty: null pointer binary search tree.\n");
        return 1;
    }

    return bst->size == 0;
}
