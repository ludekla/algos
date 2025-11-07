#ifndef LIST_H
#define LIST_H

// List node
struct Node_ {
    void* data;
    struct Node_* next;
};

typedef struct Node_ Node;

// List
typedef struct {
    unsigned int size;
    Node* head;
    Node* tail;
    void (*purge)(void* data);
    int (*match)(const void* data1, const void* data2);
} List;

void list_init(List* list, void (*purge)(void* data));

int list_insert(List* list, Node* node, const void* data);

int list_remove(List* list, Node* node, void** data);

void list_clear(List* list);

// macros
#define list_size(list) ((list)->size)

#endif
