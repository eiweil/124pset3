#include <binheap.h>

static unsigned int start_size = 1024;

Node heap_find_min(struct Heap *restrict h) {
    return h->nodes[0];
}

void free_heap(struct Heap *restrict h) {
    free(h->nodes);
}

// Initialize heap for n vertices
void heap_init(struct Heap *restrict h, Node* a, unsigned long n)
{
    start_size = n;

    struct Heap heap = {
        .sz = n,
        .n = n,
        .nodes = a
    };
    *h = heap;
    if (!h->nodes) 
        exit(1);
}

// Inserts element to the heap
void heap_insert(struct Heap *restrict h, Node node)
{

    // Realloc heap if it's full
    if (h->n == h->sz)
    {
        // increase size by power of 2
        h->sz <<= 1;
        h->nodes = realloc(h->nodes, sizeof(Node) * h->sz);
        if (!h->nodes)
            exit(1);
    }

    // insert vertex into right place in heap
    unsigned int curr, parent;
    curr = h->n++;

    while (curr > 0) {
        // parent's index is floor of (curr-1)/2
        parent = (curr - 1)/2; 

        // found where it fits
        if ((h->nodes[parent]).min_edge <= node.min_edge) 
            break;

        // swap nodes
        h->nodes[curr] = h->nodes[parent];
        curr = parent;
    }
    h->nodes[curr] = node;
}

// Removes the top vertex from the heap
void heap_deletemin(struct Heap *restrict h)
{

    // Find last vertex in heap
    Node temp = h->nodes[--(h->n)];

    printf("temp: %f\n\n", temp.min_edge);

    // Resize the heap if it's consuming too much memory
    if ((h->n <= (h->sz >> 2)) && (h->sz > start_size))
    {
        h->sz >>= 1;
        h->nodes = realloc(h->nodes, sizeof(Node) * h->sz);
        if (!h->nodes)
            exit(1);
    }

    // Fix heap
    unsigned int curr, small, big;
    curr = 0;
    while (1) {
        // Find the child to swap with
        small = curr * 2 + 1;

        // If no children, we're done
        if (small >= h->n) 
            break; 

        big = small + 1;

        // find smaller child
        if ((big < h->n) && 
            (h->nodes[big]).min_edge <= (h->nodes[small]).min_edge)
            small = big;

        // if smaller child is at least as big as parent, we're done
        if (temp.min_edge <= (h->nodes[small]).min_edge) 
            break;

        // swap
        h->nodes[curr] = h->nodes[small];
        curr = small;
    }
    h->nodes[curr] = temp;
}

// Heapifies a non-empty array
void min_heapify(Node* a, unsigned long n)
{
    unsigned int root, curr, small, big;
    Node temp;

    // only have to heapify up from penultimate layer
    root = n/2 - 1;
    while (1)
    {
        temp = a[root];
        for(curr = root; 1; curr = small)
        {
            // Find the child to swap with
            small = curr * 2 + 1;

            // if no children, subheap is done
            if (small >= n) 
                break;

            big = small + 1;

            // find smaller child
            if ((big < n) && (a[big]).min_edge <= (a[small]).min_edge)
                small = big;

            // if smaller child is bigger or equal to parent, subheap is done
            if (temp.min_edge <= (a[small]).min_edge)
                break; 

            a[curr] = a[small];
        }

        if (curr != root) 
            a[curr] = temp;

        // we're done (at actual root of heap)
        if (!root) 
            return;

        --root;
    }
}

int isPowerOfTwo (unsigned int x)
{
  return ((x != 0) && !(x & (x - 1)));
}

void printHeap (struct Heap *restrict h) {
    for (int i = 0; i < h->n; i++) {
        printf("%f  \n", (h->nodes + i)->min_edge);
        if (isPowerOfTwo(i+2))
            printf("\n");
    }
}