#include <stdlib.h>
#include <string.h>

#include "ch09_avl.h"
#include "ch09_bistree.h"

void avl_init(Avl* avl, avl_f factor, int hidden, const void* data) {
    avl->factor = factor;
    avl->hidden = hidden;
    avl->data = (void*)data;
}

// helper functions
static void rotate_left(TreeNode** node) {
    TreeNode* left = (*node)->left;
    // check which case
    if (avl_factor_get(left) == LFT_HEAVY) {
        // perform LL rotation
        (*node)->left = left->right;
        left->right = *node;
        // update balance factors
        avl_factor_set(*node, BALANCED);
        avl_factor_set(left, BALANCED);
        *node = left;
    } else {
        // perform LR rotation
        TreeNode* grandchild = left->right;
        left->right = grandchild->left;
        (*node)->left = grandchild->right;
        grandchild->left = left;
        grandchild->right = *node;
        // update balance factors
        switch (avl_factor_get(grandchild)) {
            case BALANCED:
                avl_factor_set(left, BALANCED);
                avl_factor_set(*node, BALANCED);

                break;
            case LFT_HEAVY:
                avl_factor_set(*node, RGT_HEAVY);
                avl_factor_set(left, BALANCED);
            case RGT_HEAVY:
                avl_factor_set(*node, BALANCED);
                avl_factor_set(left, LFT_HEAVY);
        }
        *node = grandchild;
        avl_factor_set(grandchild, BALANCED);
    }
}

static void rotate_right(TreeNode** node) {
    TreeNode* right = (*node)->right;
    // check which case
    if (avl_factor_get(right) == RGT_HEAVY) {
        // perform RR rotation
        (*node)->right = right->left;
        right->left = *node;
        // update balance factors
        avl_factor_set(*node, BALANCED);
        avl_factor_set(right, BALANCED);
        *node = right;
    } else {
        // perform LR rotation
        TreeNode* grandchild = right->left;
        (*node)->right = grandchild->left;
        grandchild->left = *node;
        right->left = grandchild->right;
        grandchild->right = right;
        // update balance factors
        switch (avl_factor_get(grandchild)) {
            case BALANCED:
                avl_factor_set(right, BALANCED);
                avl_factor_set(*node, BALANCED);
                break;
            case LFT_HEAVY:
                avl_factor_set(*node, BALANCED);
                avl_factor_set(right, RGT_HEAVY);
            case RGT_HEAVY:
                avl_factor_set(*node, LFT_HEAVY);
                avl_factor_set(right, BALANCED);
        }
        *node = grandchild;
        avl_factor_set(grandchild, BALANCED);
    }
}

static void free_all_data(BisTree* tree, TreeNode** pos);

static void purge_left(BisTree* tree, TreeNode* node);

static void purge_right(BisTree* tree, TreeNode* node);

static void free_all_data(BisTree* tree, TreeNode** pos) {
    // delete left-hand part below
    purge_left(tree, *pos);
    // delete right-hand part below
    purge_right(tree, *pos);
    // purge data attached to the avl
    if (tree->purge != NULL)
        tree->purge(avl_data_get(*pos));
    // free avl obj
    free((*pos)->data);
    // free node
    free(*pos);
    *pos = NULL;
}

static void purge_left(BisTree* tree, TreeNode* node) {
    // check whether there is nothing to be removed
    if (bistree_size(tree) == 0)
        // early return
        return;
    TreeNode** pos = (node == NULL) ? &tree->root : &node->left;
    // make sure there is sth to be purged
    if (*pos != NULL) {
        free_all_data(tree, pos);
    }
}

static void purge_right(BisTree* tree, TreeNode* node) {
    // check whether there is nothing to be removed
    if (bistree_size(tree) == 0)
        // early return
        return;
    TreeNode** pos = (node == NULL) ? &tree->root : &node->right;
    // make sure there is sth to be purged
    if (*pos != NULL) {
        free_all_data(tree, pos);
    }
}

static int insert(BisTree* tree, TreeNode** node, const void* data, int* bal) {
    Avl* avl;
    int retval;
    // empty tree case
    if (*node == NULL) {
        if ((avl = (Avl*)malloc(sizeof(Avl))) == NULL)
            return -1;
        avl_init(avl, BALANCED, 0, data);
        return bitree_insleft(tree, NULL, avl);
    } else {
        int cmp = tree->compare(data, avl_data_get(*node));
        if (cmp < 0) {
            if ((*node)->left == NULL) {
                // there is space available
                if ((avl = (Avl*)malloc(sizeof(Avl))) != 0)
                    return -1;
                avl_init(avl, BALANCED, 0, data);
                if (bitree_insleft(tree, *node, avl) != 0)
                    return -1;
                *bal = 0;
            } else {
                // try further down the tree
                if ((retval = insert(tree, &(*node)->left, data, bal)) != 0)
                    return retval;
            }
            if (!*bal) {
                switch (avl_factor_get(*node)) {
                    case LFT_HEAVY:
                        rotate_left(node);
                        *bal = 1;
                        break;
                    case BALANCED:
                        avl_factor_set(*node, LFT_HEAVY);
                        break;
                    case RGT_HEAVY:
                        avl_factor_set(*node, BALANCED);
                        *bal = 1;
                }
            }
        } else if (cmp > 0) {
            if ((*node)->right == NULL) {
                // there is space available
                if ((avl = (Avl*)malloc(sizeof(Avl))) != 0)
                    return -1;
                avl_init(avl, BALANCED, 0, data);
                if (bitree_insright(tree, *node, avl) != 0)
                    return -1;
                *bal = 0;
            } else {
                // try further down the tree
                if ((retval = insert(tree, &(*node)->right, data, bal)) != 0)
                    return retval;
            }
            if (!*bal) {
                switch (avl_factor_get(*node)) {
                    case LFT_HEAVY:
                        avl_factor_set(*node, BALANCED);
                        *bal = 1;
                        break;
                    case BALANCED:
                        avl_factor_set(*node, RGT_HEAVY);
                        break;
                    case RGT_HEAVY:
                        rotate_right(node);
                        *bal = 1;
                }
            }
        } else {
            // replace data if not hidden
            if (avl_hidden_get(*node))
                return 1;
            if (tree->purge != NULL)
                tree->purge(avl_data_get(*node));
            avl_data_set(*node, data);
            avl_hidden_set(*node, 0);
        }
    }
    return 0;
}

static int lookup(BisTree* tree, TreeNode* node, void** data) {
    int retval;
    if (node == NULL)
        return -1;
    int cmp = tree->compare(*data, avl_data_get(node));
    if (cmp < 0) {
        retval = lookup(tree, node->left, data);
    } else if (cmp > 0) {
        retval = lookup(tree, node->right, data);
    } else {
        // pass data
        *data = avl_data_get(node);
        retval = 0;
    }
    return retval;
}

static int hide(BisTree* tree, TreeNode* node, void** data) {
    int retval;
    if (node == NULL)
        return -1;
    int cmp = tree->compare(*data, avl_data_get(node));
    if (cmp < 0) {
        retval = hide(tree, node->left, data);
    } else if (cmp > 0) {
        retval = hide(tree, node->right, data);
    } else {
        // hide 
        avl_hidden_set(node, 1);
        retval = 0;
    }
    return retval;
}

// Public Interface
void bistree_init(BisTree* tree, compare_f compare, purge_f purge) {
    bitree_init(tree, purge);
    tree->compare = compare;
}

int bistree_insert(BisTree* tree, const void* data) {
    int balanced = 0;
    return insert(tree, &tree->root, data, &balanced);
}

int bistree_remove(BisTree* tree, void** data) {
    return hide(tree, tree->root, data);
}

int bistree_lookup(BisTree* tree, void** data) {
    return lookup(tree, tree->root, data);
}

void bistree_clear(BisTree* tree) {
    purge_left(tree, NULL);
    memset(tree, 0, sizeof(BisTree));
}
