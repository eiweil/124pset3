#include <randmst.h>

struct Heap
{
    int d; // the "fan-out" value; 2 for binary heap
    int sz; // number of vertices heap can hold
    int n; // number of vertices currently in heap
    int* pos; // keeps track of position of nodes within heap
    Node* nodes; // Array of the vertices in heap
};

// works
Node heap_find_min(struct Heap* h);

void free_heap(struct Heap* h);

int in_heap(struct Heap* h, int id);

// works
void heap_init(struct Heap* h, Node* a, int n, int d);

// works
void heap_insert(struct Heap* h, Node node);

// works
void heap_deletemin(struct Heap* h);

// works
void min_heapify(struct Heap* h);

void heap_number(struct Heap* h);

// works
int is_pwr_two (unsigned int x);

// works
void print_heap (struct Heap* h);