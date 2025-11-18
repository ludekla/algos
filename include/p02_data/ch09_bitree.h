#ifndef BITREE_H
#define BITREE_H

struct BiTreeNode_ {
    void* data;
    struct BiTreeNode_* left;
    struct BiTreeNode_* right;
};

typedef struct BiTreeNode_ BiTreeNode;

typedef struct {
    int size;
    BiTreeNode* root;
    // function pointers
    void (*purge)(void* data);
    int (*compare)(const void* key1, const void* key2); 
} BiTree;

BiTreeNode* bitree_node_new(void* data);

void bitree_init(BiTree* tree, void (*purge)(void*));

int bitree_insleft(BiTree* tree, BiTreeNode* node, void* data);

int bitree_insright(BiTree* tree, BiTreeNode* node, void* data);

void bitree_rmleft(BiTree* tree, BiTreeNode* node); 

void bitree_rmright(BiTree* tree, BiTreeNode* node);

void bitree_clear(BiTree* tree);

#define bitree_size(tree) ((tree)->size)

#define bitree_is_leaf(node) ((node)->left == NULL &&  (node)->right == NULL) 

#endif
