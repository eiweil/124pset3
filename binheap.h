#include <randmst.h>

typedef Node type;

struct Heap
{
    unsigned long sz; // number of vertices heap can hold
    unsigned long n; // number of vertices currently in heap
    Node* nodes; // Array of the vertices in heap
};

void heap_init(struct heap *restrict h);
void heap_push(struct heap *restrict h, type value);
void heap_pop(struct heap *restrict h);

// Returns the top of the heap
#define heap_front(h) (*(h)->data)

// Frees the allocated memory
#define heap_term(h) (free((h)->data))

void heapify(type data[restrict], unsigned int count);