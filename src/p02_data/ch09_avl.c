#include "ch09_avl.h"

avl_f avl_get(TreeNode* node) {
    return ((*Avl)node->data)->factor;
}

void avl_set(TreeNode* node, avl_f factor) {
    ((*Avl)node->data)->factor = factor;
}

void rotate_left(TreeNode** node) {
    TreeNode* left = (*node)->left;
    // check which case
    if (avl_get(left) == LFT_HEAVY) {
        // perform LL rotation
        (*node)->left = left->right;
        left->right = *node;
        // update balance factors
        avl_set(*node, BALANCED);
        avl_set(left, BALANCED);
        *node = left;
    } else {
        // perform LR rotation
        TreeNode* grandchild = left->right;
        left->right = grandchild->left;
        (*node)->left = grandchild->right;
        grandchild->left = left;
        grandchild->right = *node;
        // update balance factors
        switch (avl_get(grandchild)) {
            case BALANCED:
                avl_set(left, BALANCED);
                avl_set(*node, BALANCED);
                break;
            case LFT_HEAVY:
                avl_set(*node, RGT_HEAVY);
                avl_set(left, BALANCED);
            case RGT_HEAVY:
                avl_set(*node, BALANCED);
                avl_set(left, LFT_HEAVY);
        }
        *node = grandchild;
        avl_set(grandchild, BALANCED);
    }
}

void rotate_right(TreeNode** node) {
    TreeNode* right = (*node)->right;
    // check which case
    if (avl_get(right) == RGT_HEAVY) {
        // perform RR rotation
        (*node)->right = right->left;
        right->left = *node;
        // update balance factors
        avl_set(*node, BALANCED);
        avl_set(right, BALANCED);
        *node = right;
    } else {
        // perform LR rotation
        TreeNode* grandchild = right->left;
        (*node)->right = grandchild->left;
        grandchild->left = *node;
        right->left = grandchild->right;
        grandchild->right = right;
        // update balance factors
        switch (avl_get(grandchild)) {
            case BALANCED:
                avl_set(left, BALANCED);
                avl_set(*node, BALANCED);
                break;
            case LFT_HEAVY:
                avl_set(*node, BALANCED);
                avl_set(right, RGT_HEAVY);
            case RGT_HEAVY:
                avl_set(*node, LFT_HEAVY);
                avl_set(right, BALANCED);
        }
        *node = grandchild;
        avl_set(grandchild, BALANCED);
    }
}
