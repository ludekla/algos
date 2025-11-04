#ifndef STACK_H
#define STACK_H

#include <stddef.h> // for NULL

#include "ch05_list.h"

typedef List Stack;

#define stack_init list_init 

#define stack_clear list_clear 

int stack_push(Stack* stack, const void* data); 

int stack_pop(Stack* stack, void** data);

#define stack_peek(stack) ((stack)->head == NULL ? NULL : ((stack)->head)->data) 
#define stack_size(stack) ((stack)->size)

#endif
