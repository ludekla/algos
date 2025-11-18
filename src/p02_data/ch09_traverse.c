#include "ch09_traverse.h"

int preorder(BiTreeNode* node, List* list) {
    if (node == NULL)
        return 0;
    if (list_insert(list, list->tail, node->data) != 0)
        return -1;
    if (node->left != NULL && preorder(node->left, list) != 0)
        return -1;
    if (node->right != NULL && preorder(node->right, list) != 0)
        return -1;
    return 0;
}

int inorder(BiTreeNode* node, List* list) {
    if (node == NULL)
        return 0;
    if (node->left != NULL && inorder(node->left, list) != 0)
        return -1;
    if (list_insert(list, list->tail, node->data) != 0)
        return -1;
    if (node->right != NULL && inorder(node->right, list) != 0)
        return -1;
    return 0;
}

int postorder(BiTreeNode* node, List* list) {
    if (node == NULL)
        return 0;
    if (node->left != NULL && postorder(node->left, list) != 0)
        return -1;
    if (node->right != NULL && postorder(node->right, list) != 0)
        return -1;
    if (list_insert(list, list->tail, node->data) != 0)
        return -1;
    return 0;
}
