# Binary Search Tree (BST) in C

This project implements a **Binary Search Tree (BST)** data structure in C. It supports basic operations like inserting, removing, searching, and traversing elements, while keeping the implementation clean and modular for educational purposes.

## ✅ Features

- Create and destroy a binary search tree
- Insert and remove integer elements
- Search for a value in the tree
- Check if a value exists
- Get the minimum and maximum values
- Perform in-order, pre-order, and post-order traversals
- Check if the tree is empty
- Get the current number of elements
- Graceful error handling for null pointers and duplicate values

## 🔧 API Overview

```c
BST *bst_create();
void bst_destroy(BST *bst);

int bst_insert(BST *bst, int value);
int bst_remove(BST *bst, int value);

Node *bst_search(const BST *bst, int value);
int bst_contains(const BST *bst, int value);

int bst_min(const BST *bst);
int bst_max(const BST *bst);

Node *predecessor(const BST *bst, int value);
Node *successor(const BST *bst, int value);

int *bst_inorder_traverse(const BST *bst);
int *bst_preorder_traverse(const BST *bst);
int *bst_postorder_traverse(const BST *bst);

size_t bst_size(const BST *bst);
int bst_is_empty(const BST *bst);
```
For full definitions and descriptions, see bst.h.

## 🚀 Getting Started

Clone the repository:

    git clone https://github.com/IAmAliKochaki/DataStructures.git
    cd BinarySearchTree

Compile:

    gcc use.c bst.c

Run:

    ./a.out

Replace use.c with your own test file if needed.


## 🛠️ Requirements

    GCC or Clang

    Standard C Library

## 🧪 Testing

You can write your own use.c to test the features, use.c is a quick example.