#ifndef BISTREE_H
#define BISTREE_H

#include "ch09_bitree.h"

typedef int (*compare_f)(const void* key1, const void* key2);

typedef void (*purge_f)(void* data);

typedef BiTree BisTree;

void bistree_init(BisTree* tree, compare_f compare, purge_f purge);

int bistree_insert(BisTree* tree, const void* data);

int bistree_purge(BisTree* tree, void** data);

int bistree_lookup(BisTree* tree, void** data); 

void bistree_clear(BisTree* tree);

#define bistree_size(tree) ((tree)->size)

#endif
