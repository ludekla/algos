#include <stdlib.h>

#include "ch07_set.h"

void set_init(Set* set, match_fn match, void (*purge)(void* data)) {
    list_init(set, purge);
    set->match = match;
}

int set_insert(Set* set, void* data) {
    // go look whether the element is already present
    for (Node* run = set->head; run; run = run->next) {
        if (set_is_member(set, data))
            return -1;
    }
    return list_insert(set, set->tail, data);
}

int set_remove(Set* set, void** data) {
    Node* prev = NULL;
    // while looking keep track of preceding node
    for (Node* run = set->head; run; run = run->next) {
        if (set->match(run->data, *data))
            return list_remove(set, prev, data);
        prev = run;
    }
    return -1;
}

#define set_clear list_clear

int set_union(Set* setu, const Set* set1, const Set* set2) {
    set_init(setu, set1->match, NULL);
    // 1st take everything from set 1
    for (Node* run = set1->head; run; run = run->next) {
        if (set_insert(setu, run->data) != 0) {
            set_clear(setu);
            return -1;
         }
    }
    // next add everything from set 2 not already in set 1
    for (Node* run = set2->head; run; run = run->next) {
        if (set_is_member(setu, run->data))
            continue;
        if (set_insert(setu, run->data) != 0) {
            set_clear(setu);
            return -1;
        }
    }
    return 0;
}

int set_intersection(Set* seti, const Set* set1, const Set* set2) {
    set_init(seti, set1->match, NULL);
    // 1st take everything from set 1 that is also in set 2
    for (Node* run = set1->head; run; run = run->next) {
        if (!set_is_member(set2, run->data))
            continue;
        if (set_insert(seti, run->data) != 0) {
            set_clear(seti);
            return -1;
         }
    }
    return 0;
}

int set_difference(Set* setd, const Set* set1, const Set* set2) {
    set_init(setd, set1->match, NULL);
    for (Node* run = set1->head; run; run = run->next) {
        if (set_is_member(set2, run->data))
            continue;
        if (set_insert(setd, run->data) != 0) {
            set_clear(setd);
            return -1;
         }
    }
    return 0;
}

#define set_size(set) ((set)->size)

int set_is_member(const Set* set, void* data) {
    for (Node* run = set->head; run; run = run->next) {
         if (set->match(run->data, data))
            return 1;
    }
    return 0;
}

int set_is_subset(const Set* set1, const Set* set2) {
    if (set_size(set1) > set_size(set2))
        return 0;
    for (Node* run = set1->head; run; run = run->next) {
         if (!set_is_member(set2, run->data))
            return 0;
    }
    return 1;
}

int set_is_equal(const Set* set1, const Set* set2) {
    if (set_size(set1) != set_size(set2))
        return 0;
    return set_is_subset(set1, set2);
}
