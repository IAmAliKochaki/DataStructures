# AVL Tree (Self-Balancing Binary Search Tree) in C

This project implements an **AVL Tree** in C — a **self-balancing binary search tree** where the heights of subtrees differ by at most one. Balancing is achieved automatically during insertions and deletions using tree rotations.

It supports create, destroy, insert, and remove operations with **automatic balancing** to maintain **O(log n)** performance.

## 👉 Note:
- Since operations like search, get, and traversals are essentially the same as in a regular Binary Search Tree (BST), this implementation focuses only on insert and remove (plus create and destroy) as the AVL-specific parts.

## ✅ Features

- Create and destroy an AVL Tree
- Insert integer values with automatic balancing
- Remove integer values while maintaining balance
- Duplicate handling (insertion of an existing value fails gracefully)
- Automatic height updates and rotations (R, L, Rl, LR)
- Tracks tree size
- Modular and educational design

## 🔧 API Overview

```c
AVLTree *avlt_create();
void avlt_destroy(AVLTree *avlt);

int avlt_insert(AVLTree *avlt, int value);
int avlt_remove(AVLTree *avlt, int value);
```
For full definitions and descriptions, see avlt.h.
