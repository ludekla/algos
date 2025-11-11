#ifndef SET_H
#define SET_H

#include "ch05_list.h"

typedef List Set;

void set_init(Set* set, match_fn match, purge_fn purge); 

int set_insert(Set* set, void* data);

int set_remove(Set* set, void** data);

#define set_clear list_clear

int set_union(Set* setu, const Set* set1, const Set* set2); 

int set_intersection(Set* seti, const Set* set1, const Set* set2); 

int set_difference(Set* setd, const Set* set1, const Set* set2); 

#define set_size(set) ((set)->size)

int set_is_member(const Set* set, void* data);

int set_is_subset(const Set* set1, const Set* set2); 

int set_is_equal(const Set* set1, const Set* set2); 

#endif
