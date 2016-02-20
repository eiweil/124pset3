#include <randmst.h>

struct Heap
{
    int sz; // number of vertices heap can hold
    int n; // number of vertices currently in heap
    Node* nodes; // Array of the vertices in heap
};

// works
Node heap_find_min(struct Heap *restrict h);

void free_heap(struct Heap *restrict h);

// works
void heap_init(struct Heap *restrict h, Node* a, int n);

// works
void heap_insert(struct Heap *restrict h, Node node);

// works
void heap_deletemin(struct Heap *restrict h);

// works
void min_heapify(Node* a, int n);

// works
int isPowerOfTwo (unsigned int x);

// works
void printHeap (struct Heap *restrict h);