#include <stdlib.h>

#include "ch07_cover.h"

int best_subset(Set* set, Set* subsets, Set** best) {
    int max_size = 0;
    // intersection set
    Set* seti;
    // pointer to maximum overlap set
    Set* best_set = NULL;     
    for (Node* run = subsets->head; run; run = run->next) {
        Set* subset = (Set*)run->data;
        if (set_intersection(seti, set, subset) != 0)
            return -1;
        if (set_size(seti) > max_size) {
            best_set = subset;
            max_size = set_size(seti);
        }
        set_clear(seti);
    }
    if (best_set == NULL)
        // all intersections have been empty
        return -1;
    // store pointer to best subset
    *best = best_set;
    // all is aces
    return 0;
}

int min_cover(Set* set, Set* subsets, Set* cover) {
    set_init(cover, subsets->match, NULL);
    Set* best_set;
    while (set_size(set) > 0 && set_size(subsets) > 0) {
        if (best_subset(set, subsets, &best_set) != 0)
            return -1;
        // remove every element of the set in best_set
        for (Node* run = best_set->head; run; run = run->next) {
             if (set_remove(set, run->data) != 0)
                return -1;
        }
        // remove best_set from subsets
        if (set_remove(subsets, (void**)&best_set) != 0)
            return -1;
        // add best_set to the cover
        if (set_insert(cover, best_set) != 0)
            return -1;
    }
    // all good
    return 0;
}
