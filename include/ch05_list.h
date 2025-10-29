#ifndef LIST_H
#define LIST_H

// List node
struct ListNode_ {
    void* data;
    struct ListNode_* next;
};

typedef struct ListNode_ ListNode;

// List
typedef struct List_ {
    unsigned int size;
    ListNode* head;
    ListNode* tail;
    void (*purge)(void* data);
} List;

void list_init(List* list, void (*purge)(void* data));

int list_insert(List* list, ListNode* node, const void* data);

int list_remove(List* list, ListNode* node, void** data);

void list_clear(List* list);

// macros
#define list_size(list) ((list)->size)

#endif
