#include <randmst.h>

struct Heap
{
    int sz; // number of vertices heap can hold
    int n; // number of vertices currently in heap
    int* pos; // keeps track of position of nodes within heap
    Node* nodes; // Array of the vertices in heap
};

// works
Node heap_find_min(struct Heap* restrict h);

void free_heap(struct Heap* restrict h);

int in_heap(struct Heap* restrict h, int id);

// works
void heap_init(struct Heap* restrict h, Node* a, int n);

// works
void heap_insert(struct Heap* restrict h, Node node);

// works
void heap_deletemin(struct Heap* restrict h);

// works
void min_heapify(struct Heap* restrict h, int n);

void heap_number(struct Heap* restrict h);

// works
int is_pwr_two (unsigned int x);

// works
void print_heap (struct Heap* restrict h);