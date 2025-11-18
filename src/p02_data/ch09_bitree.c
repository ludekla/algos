#include <stdlib.h>
#include <string.h>

#include "ch09_bitree.h"

BiTreeNode* bitree_node_new(void* data) {
    BiTreeNode* new_node;
    if ((new_node = (BiTreeNode*)malloc(sizeof(BiTreeNode))) == NULL)
        return NULL;
    new_node->data = data;
    new_node->left = new_node->right = NULL;
    return new_node;
}

void bitree_init(BiTree* tree, void (*purge)(void*)) {
    tree->size = 0;
    tree->root = NULL;
    tree->purge = purge;
}

int bitree_insleft(BiTree* tree, BiTreeNode* node, void* data) {
    BiTreeNode** pos = (node == NULL) ? &tree->root : &node->left;
    // position must not be occupied
    if (*pos != NULL)
        return -1;
    BiTreeNode* new_node = bitree_node_new(data);  
    if (new_node == NULL)
        return -1;
    *pos = new_node;
    return 0;
}

int bitree_insright(BiTree* tree, BiTreeNode* node, void* data) {
    BiTreeNode** pos = (node == NULL) ? &tree->root : &node->right;
    // position must not be occupied
    if (*pos != NULL)
        return -1;
    BiTreeNode* new_node = bitree_node_new(data);  
    if (new_node == NULL)
        return -1;
    *pos = new_node;
    return 0;
}

void bitree_rmleft(BiTree* tree, BiTreeNode* node) {
    // remove left child of node
    if (bitree_size(tree) == 0)
        return;
    BiTreeNode** pos = (node == NULL) ? &tree->root : &node->left;
    if (*pos != NULL) {
        bitree_rmleft(tree, *pos); 
        bitree_rmright(tree, *pos);
        if (tree->purge != NULL)
            tree->purge((*pos)->data);
        free(*pos);
        tree->size--;
    }
}

void bitree_rmright(BiTree* tree, BiTreeNode* node) {
    // remove right child of node
    if (bitree_size(tree) == 0)
        return;
    BiTreeNode** pos = (node == NULL) ? &tree->root : &node->right;
    if (*pos != NULL) {
        bitree_rmleft(tree, *pos); 
        bitree_rmright(tree, *pos);
        if (tree->purge != NULL)
            tree->purge((*pos)->data);
        free(*pos);
        tree->size--;
    }
}

void bitree_clear(BiTree* tree) {
    // delete all nodes
    bitree_rmleft(tree, NULL);
    memset(tree, 0, sizeof(BiTree));
}
