#ifndef AVL_H
#define AVL_H

#include "ch09_bitree.h"

// AVL balance factor type
typedef enum {
    BALANCED,
    RGT_HEAVY,
    LFT_HEAVY
} avl_f;

// AVL node
typedef struct {
    void* data;
    avl_f factor;
} Avl;

avl_f avl_get(TreeNode* node);

void avl_set(TreeNode* node, avl_f factor);

void rotate_left(TreeNode** node); 

void rotate_right(TreeNode** node); 

#endif
