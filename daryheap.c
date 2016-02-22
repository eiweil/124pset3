#include <daryheap.h>

static unsigned int start_size = 1024;

Node heap_find_min(struct Heap* h) {
    return h->nodes[0];
}

void free_heap(struct Heap* h) {
    free(h->pos);
}

int in_heap(struct Heap* h, int id) {
    if (h->pos[id] < h->n && h->pos[id] != -1)
        return 1;
    else
        return 0;
}

// Initialize heap for n vertices
void heap_init(struct Heap* h, Node* a, int n, int d)
{
    start_size = n;

    struct Heap heap = {
        .d = d,
        .sz = n,
        .n = n,
        .pos = (int*) malloc((n+1) * sizeof(Node)),
        .nodes = a
    };
    *h = heap;
    if (!h->nodes) 
        exit(1);

}

// Inserts element to the heap
void heap_insert(struct Heap* h, Node node)
{

    int d = h->d;

    // Realloc heap if it's full
    if (h->n == h->sz)
    {
        // increase size by power of 2
        h->sz <<= 1;
        h->nodes = (Node*) realloc(h->nodes, sizeof(Node) * h->sz);
        if (!h->nodes)
            exit(1);
    }

    // insert vertex into right place in heap
    unsigned int curr, parent;
    curr = h->n++;

    while (curr > 0) {
        // parent's index is floor of (curr-1)/d
        parent = (curr - 1)/d; 

        // found where it fits
        if ((h->nodes[parent]).min_edge <= node.min_edge) 
            break;

        // swap nodes
        h->nodes[curr] = h->nodes[parent];
        h->pos[(h->nodes[parent]).id] = curr;
        curr = parent;
    }
    h->nodes[curr] = node;
    h->pos[node.id] = curr;
}

// Removes the top vertex from the heap
void heap_deletemin(struct Heap* h)
{

    int d = h->d;

    // Find last vertex in heap
    Node temp = h->nodes[--(h->n)];

    // remove min from heap
    h->pos[h->nodes[0].id] = -1;

    //printf("temp: %f\n\n", temp.min_edge);

    // Resize the heap if it's consuming too much memory
    if ((h->n <= (h->sz >> 2)) && (h->sz > start_size))
    {
        h->sz >>= 1;
        h->nodes = realloc(h->nodes, sizeof(Node) * h->sz);
        if (!h->nodes)
            exit(1);
    }

    // Fix heap
    unsigned int curr, first, small;
    curr = 0;
    while (1) {
        // Find the child to swap with
        first = curr * d + 1;

        // If no children, we're done
        if (first >= h->n) 
            break; 

        // find smallest child
        small = first;
        for (int i = 1; i <= d; i++) {
            if ((first + i) < h->n && 
                    (h->nodes[first + i]).min_edge <= (h->nodes[small]).min_edge)
                small = first + i;
        }
/*
        // find smaller child
        if ((big < h->n) && 
            (h->nodes[big]).min_edge <= (h->nodes[small]).min_edge)
            small = big;
*/
        // found place for temp
        if (temp.min_edge <= (h->nodes[small]).min_edge) 
            break;

        // move child up
        h->nodes[curr] = h->nodes[small];
        h->pos[(h->nodes[small]).id] = curr;
        curr = small;
    }
    h->nodes[curr] = temp;
    h->pos[temp.id] = curr;
}

// Heapifies a non-empty array
void min_heapify(struct Heap* h)
{

    int d = h->d;

    Node* nodes = h->nodes;
    unsigned int root, curr, first, small;
    Node temp;

    // only have to heapify up from last node that has children
    root = ((h->n)-2)/d;
    //printf("root: %d\n", root);
    while (1)
    {
        temp = nodes[root];
        //printf("temp id: %d\n", temp.id);
        curr = root;
        while (1)
        {
            // Find the child to swap with
            first = curr * d + 1;

            // if no children, subheap is done
            if (first >= h->n) 
                break;

             // find smallest child
            small = first;
            for (int i = 1; i < d; i++) {
                if ((first + i) < h->n && 
                    (h->nodes[first + i]).min_edge <= (h->nodes[small]).min_edge)
                    small = first + i;
            }
            //printf("small edge: %f\n", (h->nodes[small]).min_edge);
/*
            // find smaller child
            if ((big < n) && (nodes[big]).min_edge <= (nodes[small]).min_edge)
                small = big;
*/
            // if smaller child is bigger or equal to parent, subheap is done
            if (temp.min_edge <= (nodes[small]).min_edge)
                break; 

            nodes[curr] = nodes[small];
            h->pos[nodes[small].id] = curr;
            curr = small;
        }

        if (curr != root) {
            nodes[curr] = temp;
            h->pos[temp.id] = curr;
        }
            
        // we're done (at actual root of heap)
        if (!root) 
            return;

        --root;
    }
}

void heap_number(struct Heap* h) {
    for (int i = 0; i < h->n; i++) {
        h->pos[i+1] = i;
    }
}

int is_pwr_d (unsigned int n, int d)
{
    if (n == 0)
        return 0;
    while (n % d == 0) {
        n /= d;
    }
    return n == 1;
}

void print_heap (struct Heap* h) {
    int d = h->d;
    int counter = 0;
    int level = 0;
    while (counter != h->n) {
        for (int j = 0; j < pow(d, level); j++) {
            printf("%d / %d / %f\n", 
                (h->nodes[counter]).id, 
                h->pos[h->nodes[counter].id], 
                h->nodes[counter].min_edge);
            counter++;
            if (counter == h->n)
                break;
        }
        level++;
        printf("\n");
    }
    printf("-----------------------------\n");
}