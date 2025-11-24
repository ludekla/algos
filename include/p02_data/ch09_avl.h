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
    int hidden;
} Avl;

void avl_init(Avl* avl, avl_f factor, int hidden, const void* data);

#define avl_factor_get(node) (((Avl*)(node)->data)->factor)

#define avl_factor_set(node, val) (((Avl*)(node)->data)->factor = (val))

#define avl_data_get(node) (((Avl*)(node)->data)->data)

#define avl_data_set(node, val) (((Avl*)(node)->data)->data = (void*)(val))

#define avl_hidden_get(node) (((Avl*)(node)->data)->hidden)

#define avl_hidden_set(node, val) (((Avl*)(node)->data)->hidden = (val))

#endif
