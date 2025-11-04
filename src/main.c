#include <stdio.h>

#include "ch05_list.h"
#include "ch06_stack.h"

void purge(void* v) {
    int* p = (int*)v;
    printf("Not really purging: %d\n", *p);
}

int main() {

    Stack stack;

    stack_init(&stack, purge);
   
    int a[3] = {0, 1, 2};

    
    for (int i = 0; i < 3; i++) {
        int size = stack_size(&stack);
        printf("Stack size before push: %u\n", size);
        stack_push(&stack, a + i);
        printf("Stack size after push: %u\n", stack_size(&stack));
    }
    
    int* data;
    
    if ((data = (int*)stack_peek(&stack)) != NULL)
        printf("Peek: %d\n", *data); 
    
    while ((stack_pop(&stack, (void**)&data) == 0)) {
        int size = stack_size(&stack);
        printf("Successfully popped: %d (size now: %u)\n", *data, size);
        if ((data = (int*)stack_peek(&stack)) != NULL)
            printf("Peek: %d\n", *data); 
    }

    stack_clear(&stack);

    return 0;
}

