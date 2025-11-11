#ifndef LIST_H
#define LIST_H

typedef int (*match_fn)(const void* key1, const void* key2);

typedef void (*purge_fn)(void* data);

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
    match_fn match;  // needed by other structures
    purge_fn purge;
} List;

void list_init(List* list, void (*purge)(void* data));

int list_insert(List* list, Node* node, const void* data);

int list_remove(List* list, Node* node, void** data);

void list_clear(List* list);

// macros
#define list_size(list) ((list)->size)

#endif
