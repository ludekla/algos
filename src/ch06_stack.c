#include "ch05_list.h"
#include "ch06_stack.h"

int stack_push(Stack* stack, const void* data) {
    return list_insert(stack, NULL, data);
}

int stack_pop(Stack* stack, void** data) {
    return list_remove(stack, NULL, data);
}
