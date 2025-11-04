#include <stdio.h>

#include "ch05_list.h"

void purge(void* v) {
    int* p = (int*)v;
    printf("Not really purging: %d\n", *p);
}

int main() {

    List list;

//    list_init(&list, NULL);
    list_init(&list, purge);
   
    int a[3] = {0, 1, 2};

    printf("List size: %u\n", list_size(&list));
    
    for (int i = 0; i < 3; i++) {
        list_insert(&list, NULL, a + i);
        printf("List size: %u\n", list_size(&list));
    }
    
    ListNode* run = list.head;
    while (run) {
        int* v = (int*)run->data;
        printf(" %d", *v);
        run = run->next;
    }
    printf("\n");

    run = NULL;
    list_clear(&list);

    return 0;
}

