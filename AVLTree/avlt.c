#include <stdio.h>
#include <stdlib.h>
#include "avlt.h"

static inline int MAX(int a, int b) { return (a > b) ? a : b; }

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

static void free_avlt_nodes(AVLTNode *node)
{
    if (!node)
        return;
    free_avlt_nodes(node->left);  // Free left subtree
    free_avlt_nodes(node->right); // Free right subtree
    free(node);                   // Free the node
}

void avlt_destroy(AVLTree *avlt)
{
    if (!avlt)
    {
        fprintf(stderr, "avlt_destroy: null pointer avl-tree.\n");
        return;
    }

    free_avlt_nodes(avlt->root);
    free(avlt);
}

static int get_height(AVLTNode *node)
{
    return !node ? 0 : node->height;
}

static void update_height(AVLTNode *node)
{
    if (node)
        node->height = 1 + MAX(get_height(node->left), get_height(node->right));
}

static int get_balance_factor(AVLTNode *node)
{
    return !node ? 0 : get_height(node->left) - get_height(node->right);
}

static AVLTNode *rotate_right(AVLTNode *node)
{
    if (!node)
        return NULL;
    AVLTNode *temp = node->left;
    node->left = temp->right;
    if (temp->right)
        temp->right->parent = node;
    temp->right = node;
    temp->parent = node->parent;
    node->parent = temp;
    update_height(node);
    update_height(temp);
    return temp;
}

static AVLTNode *rotate_left(AVLTNode *node)
{
    if (!node)
        return NULL;
    AVLTNode *temp = node->right;
    node->right = temp->left;
    if (temp->left)
        temp->left->parent = node;
    temp->left = node;
    temp->parent = node->parent;
    node->parent = temp;
    update_height(node);
    update_height(temp);
    return temp;
}

static AVLTNode *create_node(int value)
{
    AVLTNode *new_node = (AVLTNode *)malloc(sizeof(AVLTNode));
    if (!new_node)
        return NULL;

    new_node->key = value;
    new_node->left = new_node->right = new_node->parent = NULL;
    new_node->height = 1;
    return new_node;
}

static AVLTNode *balance_node(AVLTNode *node)
{
    update_height(node);
    int balance_factor = get_balance_factor(node);

    if (balance_factor > 1)
    {
        if (get_balance_factor(node->left) < 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }
    else if (balance_factor < -1)
    {
        if (get_balance_factor(node->right) > 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }
    return node;
}

static void balancer(AVLTree *avlt, AVLTNode *node)
{
    while (node)
    {
        node = balance_node(node);

        // Reconnect parent or update root
        if (!node->parent)
            avlt->root = node;

        update_height(node);
        node = node->parent;
    }
}
static int insert_to_tree(AVLTree *avlt, AVLTNode *new_node)
{
    AVLTNode *current = avlt->root;
    AVLTNode *previous = NULL;

    while (current)
    {
        previous = current;
        if (new_node->key < current->key)
            current = current->left;
        else if (new_node->key > current->key)
            current = current->right;
        else
        {
            free(new_node);
            return 0;
        }
    }

    if (new_node->key < previous->key)
        previous->left = new_node;
    else
        previous->right = new_node;

    new_node->parent = previous;
    avlt->size++;

    balancer(avlt, new_node);

    return 1;
}

int avlt_insert(AVLTree *avlt, int value)
{
    if (!avlt)
    {
        fprintf(stderr, "avlt_insert: null pointer avl-tree.\n");
        return 0;
    }

    AVLTNode *new_node = create_node(value);
    if (!new_node)
    {
        fprintf(stderr, "avlt_insert: node creation failed\n");
        return 0;
    }

    if (!avlt->root)
    {
        avlt->root = new_node;
        avlt->size++;
        return 1;
    }

    if (insert_to_tree(avlt, new_node) == 0)
    {
        fprintf(stderr, "avlt_insert: insertion failed.\n");
        return 0;
    }

    return 1;
}

static AVLTNode *find_node_by_value(AVLTree *avlt, int value)
{
    AVLTNode *current = avlt->root;

    while (current)
    {
        if (value < current->key)
            current = current->left;
        else if (value > current->key)
            current = current->right;
        else
            return current;
    }

    return NULL;
}

static void transplant(AVLTree *avlt, AVLTNode *old_child, AVLTNode *new_child)
{
    // old_child is root
    if (!old_child->parent)
        avlt->root = new_child;
    else if (old_child == old_child->parent->left)
        old_child->parent->left = new_child;
    else
        old_child->parent->right = new_child;
    if (new_child)
        new_child->parent = old_child->parent;
}

static AVLTNode *min_node(AVLTNode *node)
{
    while (node->left)
        node = node->left;
    return node;
}

static int remove_node_from_tree(AVLTree *avlt, int value)
{
    AVLTNode *node = find_node_by_value(avlt, value);
    if (!node)
    {
        fprintf(stderr, "remove_node_from_tree: try for remove an instance (%d) but it's not exist.\n", value);
        return 0;
    }

    AVLTNode *balance_start = node->parent;

    if (!node->left)
        transplant(avlt, node, node->right);
    else if (!node->right)
        transplant(avlt, node, node->left);
    else
    {
        AVLTNode *n_s_root = min_node(node->right); // successor
        balance_start = n_s_root->parent;
        if (n_s_root->parent != node)
        {
            transplant(avlt, n_s_root, n_s_root->right);
            n_s_root->right = node->right;
            node->right->parent = n_s_root;
        }
        transplant(avlt, node, n_s_root);
        n_s_root->left = node->left;
        node->left->parent = n_s_root;
        balance_start = n_s_root;
    }

    free(node);
    avlt->size--;

    if (balance_start)
        balancer(avlt, balance_start);
    return 1;
}

int avlt_remove(AVLTree *avlt, int value)
{
    if (!avlt)
    {
        fprintf(stderr, "avlt_remove: null pointer avl-tree.\n");
        return 0;
    }

    if (avlt->size <= 0)
    {
        fprintf(stderr, "avlt_remove: the tree is empty.\n");
        return 0;
    }

    if (remove_node_from_tree(avlt, value) == 0)
    {
        fprintf(stderr, "avlt_remove: deletion failed.\n");
        return 0;
    }

    return 1;
}