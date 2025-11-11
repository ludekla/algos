#include <string.h>
#include <stdlib.h>

#include "ch05_list.h"

void list_init(List* list, purge_fn purge) {
    list->size = 0;
    list->head = list->tail = NULL;
    list->purge = purge;
    list->match = NULL;
}

int list_insert(List* list, Node* node, const void* data) {
    // allocate memory for a new node
    Node* new_node;
    if ((new_node = (Node*)malloc(sizeof(Node))) == NULL) {
        return -1;
    }
    new_node->data = (void*)data;
    if (node == NULL) {
        // in front of the head node or as a first node
        new_node->next = list->head;
        list->head = new_node;
    } else {
        // node is pointing to a Node
        new_node->next = node->next; 
        node->next = new_node;
    }
    if (list_size(list) == 0 || node == list->tail)
        // readjust tail pointer if necessary
        list->tail = new_node;
    list->size++;
    return 0;
}

int list_remove(List* list, Node* node, void** data) {
    Node* old_node;
    if (list_size(list) == 0 || node == list->tail)
        return -1;
    if (node == NULL) {
        // head node to be removed 
        old_node = list->head;
        list->head = old_node->next;
        if (list_size(list) == 1)
            list->tail = NULL;
    } else {
        // node to be removed is behind head node
        old_node = node->next;
        node->next = old_node->next;
        if (old_node == list->tail)
            // tail node is the one to be removed
            list->tail = node;
    }
    *data = old_node->data;
    free(old_node);
    list->size--;
    return 0;
}

void list_clear(List* list) {
    void* data;
    while (list_size(list) > 0) {
        if (list_remove(list, NULL, &data) == 0 && list->purge != NULL)
            list->purge(data);
    }
    // void memset(void* block, int c, size_t size);
    // copies the value 0 as unsign char (byte) into the memory
    // block occupied by the List struct, it is not deallocated, ie freed!
    memset(list, 0, sizeof(list));
}
