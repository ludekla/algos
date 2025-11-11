#ifndef CHTABLE_H
#define CHTABLE_H

#include "ch05_list.h"

typedef int (*hash_fn)(const void* key);

typedef struct {
    int size;
    int n_buckets;
    List* buckets;
    // function pointers
    hash_fn hash;
    match_fn match;
    purge_fn purge;
} CHTable;

int chtable_init(
    CHTable* tb, 
    int n_buckets,
    hash_fn hash, match_fn match, purge_fn purge
); 

int chtable_insert(CHTable* tb, void* data);

int chtable_lookup(CHTable* tb, void* data);

int chtable_remove(CHTable* tb, void* data);

void chtable_clear(CHTable* tb);

#define chtable_size(tb) ((tb)->size)

#endif
