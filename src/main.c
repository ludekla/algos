#include <stdio.h>

#include "ch07_set.h"

int match_int(const void* data1, const void* data2) {
    return *(int*)data1 == *(int*)data2;
}

void set_print(Set* set) {
    printf("List{");
    for (Node* run = set->head; run; run = run->next)
        printf(" node: %d", *(int*)run->data);
    printf(" }\n");
}

void verbose_insert(Set* set, int *arr, int i) {
    printf("Set size before insert: %d\n", set_size(set));
    set_print(set);
    if (set_insert(set, (arr + i)) != 0)
        printf("Cannot insert %d\n", arr[i]);
    set_print(set);
    printf("Set size after insert: %d\n", set_size(set));
}

int main() {

    Set set;
    set_init(&set, match_int, NULL);

    int a[4] = {0, 1, 2, 3};
    int b[4] = {2, 3, 4, 5};

    for (int i = 0; i < 4; i++) {
        verbose_insert(&set, a, i);
    }

    for (int i = 0; i < 4; i++) {
        verbose_insert(&set, b, i);
    }

    set_clear(&set);

    return 0;
}

