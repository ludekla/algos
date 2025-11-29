#ifndef HEAP_H
#define HEAP_H

typedef int (*compare_f)(const void* key1, const void* key2); 

typedef void (*purge_f)(void *data);

typedef struct {
    int size;
    int cap;
    void** tree;
    // utilities
    compare_f compare;
    purge_f purge;
} Heap;

void heap_init(Heap* heap, compare_f compare, purge_f purge);

void heap_clear(Heap* heap);

int heap_insert(Heap* heap, const void* data);

int heap_extract(Heap* heap, void** data);

#define heap_size(heap) ((heap)->size)

#define heap_cap(heap) ((heap)->cap)

#define heap_parent(pos) ((int) (((pos) - 1) / 2))

#define heap_left(pos) (2 * (pos) + 1)

#define heap_right(pos) (2 * (pos) + 2)

#endif
