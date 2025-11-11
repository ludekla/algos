#include <stdlib.h> // malloc
#include <string.h> // memset

#include "ch08_chtable.h"

int chtable_init(
    CHTable* tb, 
    int n_buckets,
    hash_fn hash, match_fn match, purge_fn purge
) {
    tb->size = 0;
    tb->n_buckets = n_buckets;
    // allocate space for buckets
    if ((tb->buckets = (List*)malloc(n_buckets * sizeof(List))) == NULL)
        return -1;
    // initialise buckets
    for (int i = 0; i < n_buckets; i++)
        list_init(tb->buckets + i, purge);
    tb->match = match;
    tb->purge = purge;
    tb->hash = hash;
    return 0;
}

int chtable_insert(CHTable* tb, void* data) {
    // compute hash coding
    int bucket_idx = tb->hash(data) % tb->n_buckets;
    List* bucket = tb->buckets + bucket_idx; 
    // check whether data is already in table
    if (chtable_lookup(tb, data))
        // yes, data already in hash table
        return 1;
    // you can insert it now
    if (list_insert(bucket, NULL, data) != 0)
         // sth went wrong
         return -1;
    return 0;
}

int chtable_lookup(CHTable* tb, void* data) {
    int bucket_idx = tb->hash(data) % tb->n_buckets;
    List* bucket = tb->buckets + bucket_idx;
    for (Node* run = bucket->head; run; run = run->next) {
         if (tb->match(data, run->data))
            // found
            return 1;
    }
    // not found
    return 0;
}

int chtable_remove(CHTable* tb, void* data) {
    // compute hash coding
    int bucket_idx = tb->hash(data) % tb->n_buckets;
    List* bucket = tb->buckets + bucket_idx; 
    // visit the bucket 
    Node* prev = NULL;
    for (Node* run = bucket->head; run; run = run->next) {
        if (!tb->match(run->data, data))
            continue;
        // found
        if (list_remove(bucket, prev, &data) != 0)
            // sth went wrong
            return -1;
    }
    tb->size--;
    return 0;
}

void chtable_clear(CHTable* tb) {
    for (int i = 0; i < tb->n_buckets; i++)
        list_clear(tb->buckets + i);
    free(tb->buckets);
    tb->size = 0;
    memset(tb, 0, sizeof(CHTable));
}
