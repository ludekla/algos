#include <stdio.h>
#include <math.h>

#include "ch08_chtable.h"

int match_ints(const void* data1, const void* data2) {
    return *(int*)data1 == *(int*)data2;
}

int hashf(const void* key) {
    int* p = (int*)key;
    int coding = *p * 1699 + 3; 
    return coding;
}

void list_print(List* list) {
    printf("Bucket { ");
    for (Node* run = list->head; run; run = run->next)
        printf("%d ", *((int*)run->data));
    printf("}\n");
}

void chtable_print(CHTable* tb) {
    int n_buckets = tb->n_buckets;
    printf("Hash Table %d {\n", tb->size);
    for (int i = 0; i < n_buckets; i++) {
        printf("%2d ", i + 1);
        list_print(tb->buckets + i);
    }
    printf("}\n");
}

int main() {

    int a[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    CHTable tb;
    chtable_init(&tb, 10, hashf, match_ints, NULL);

    for (int i = 0; i < 12; i++) {
        chtable_insert(&tb, a + i);
    }
    chtable_print(&tb);
    printf("Delete 7\n");
    chtable_remove(&tb, a + 7);
    chtable_print(&tb);
    printf("Delete 1\n");
    chtable_remove(&tb, a + 1);
    chtable_print(&tb);
    printf("Try to insert 2\n");
    int r = chtable_insert(&tb, a + 2);
    printf("Response r: %d (meaning: ", r);
    switch (r) {
        case 0:
            printf("Insertion Success)\n");
            break;
        case 1:
            printf("Insertion Failure, key already exists)\n");
            break;
        case -1:
            printf("Insertion Failure, sth went wrong)\n");
    }
    chtable_print(&tb);
    
    // clean up
    chtable_clear(&tb);

    return 0;
}

