#ifndef BITREE_H
#define BITREE_H

typedef void (*purge_f)(void* data);

typedef int (*compare_f)(const void* key1, const void* key2); 

struct TreeNode_ {
    void* data;
    struct TreeNode_* left;
    struct TreeNode_* right;
};

typedef struct TreeNode_ TreeNode;

typedef struct {
    int size;
    TreeNode* root;
    // function pointers
    purge_f purge;
    compare_f compare;
} BiTree;

TreeNode* bitree_node_new(void* data);

void bitree_init(BiTree* tree, purge_f purge);

int bitree_insleft(BiTree* tree, TreeNode* node, void* data);

int bitree_insright(BiTree* tree, TreeNode* node, void* data);

void bitree_rmleft(BiTree* tree, TreeNode* node); 

void bitree_rmright(BiTree* tree, TreeNode* node);

void bitree_clear(BiTree* tree);

int bitree_merge(BiTree* tree, BiTree* left, BiTree* right, void* data);

#define bitree_size(tree) ((tree)->size)

#define bitree_is_leaf(node) ((node)->left == NULL &&  (node)->right == NULL) 

#endif
