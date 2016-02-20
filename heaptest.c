#include <binheap.h>
#include <pcg_basic.h>
#include <heaptest.h>

#define N 15

int main() {

    Node* nodes = calloc(N, sizeof(Node));

    struct Heap heap;
    heap_init(&heap, nodes, N);

    pcg32_random_t rng1;
    pcg32_srandom_r(&rng1, time(NULL), (intptr_t)&rng1);

    for (int i = 0; i < N; i++) {
        Node* newnode = nodes + i;
        newnode->id = i;
        newnode->min_edge = 100 * (float) pcg32_random_r(&rng1) / UINT32_MAX;
    }
    printf("unordered: \n");
    printHeap(&heap);

    min_heapify(heap.nodes, N);

    printf("ordered: \n");
    printHeap(&heap);

    printf("min: %f\n\n", heap_find_min(&heap).min_edge);

    heap_deletemin(&heap);

    printf("deletemin: \n");
    printHeap(&heap);

    Node n = {.min_edge = 2.0};

    heap_insert(&heap, n);

    printf("\ninsert: \n");
    printHeap(&heap);

    for (int i = 0; i < N; i++) {
        printf("min: %f\n\n", heap_find_min(&heap).min_edge);
        heap_deletemin(&heap);
        printHeap(&heap);
    }

    free_heap(&heap);

}