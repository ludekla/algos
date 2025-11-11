/*
*   This example is from the textbook
*
*   Cormen, Leiserson, Rivest & Stein: Introduction to Algorithms
*   The MIT Press, 2022, 4th edition
*
*/
#include <stdio.h>

#include "ch07_set.h"
#include "ch07_cover.h"

int match_ints(const void* data1, const void* data2) {
    return *(int*)data1 == *(int*)data2;
}

int match_subsets(const void* data1, const void* data2) {
    return data1 == data2;
}

void set_print(Set* set) {
    printf("Set {");
    for (Node* run = set->head; run; run = run->next)
        printf(" %d", *(int*)run->data);
    printf(" }\n");
}

int insert_ints(Set *set, int* a, int size) {
    for (int i = 0; i < size; i++) {
         if (set_insert(set, a + i) != 0)
            printf("WARNING: cannot insert %d\n", *(a+i));
    }
}

int main() {

    Set set;
    set_init(&set, match_ints, NULL);

    int a[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    insert_ints(&set, a, 12);
    printf("Set:\n");
    set_print(&set);

    Set subsets[6]; 
    // prepare subsets
    for (int i = 0; i < 6; i++)
        set_init(subsets + i, match_ints, NULL);
    
    int s1[6] = {0, 1, 2, 3, 4, 5};
    insert_ints(subsets, s1, 6);

    int s2[4] = {4, 5, 7, 8};
    insert_ints(subsets + 1, s2, 4);
   
    int s3[4] = {0, 3, 6, 9};
    insert_ints(subsets + 2, s3, 4);

    int s4[5] = {1, 4, 6, 7, 10};
    insert_ints(subsets + 3, s4, 5);

    int s5[4] = {2, 5, 8, 11};
    insert_ints(subsets + 4, s5, 4);

    int s6[2] = {9, 10};
    insert_ints(subsets + 5, s6, 2);

    Set family;
    set_init(&family, match_subsets, NULL);

    for (int i = 0; i < 6; i++) {
        if (set_insert(&family, subsets + i) != 0)
            printf("Cannot insert subset %d\n", i + 1);
    }
    // have a look at the subsets
    printf("Subsets:\n");
    int i = 0;
    for (Node* run = family.head; run; run = run->next) {
        printf("Set %d: ", ++i);
        set_print((Set*)run->data);
    }

    Set cover;
    if (greedy_cover(&set, &family, &cover) != 0)
        printf("ERROR: min_cover failed\n");

    printf("Minimum-size cover:\n");
    for (Node* run = cover.head; run; run = run->next)
        set_print(run->data);

    // clean up (not necessary, no heap alloc)
    for (int i = 0; i < 6; i++)
        set_clear(subsets + i);
    set_clear(&set);

    return 0;
}

