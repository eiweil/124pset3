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
        Node* newnode = heap.nodes + i;
        newnode->id = i;
        newnode->min_edge = 100 * (float) pcg32_random_r(&rng1) / UINT32_MAX;
    }

    heap_number(&heap);

    printf("unordered: \n");
    print_heap(&heap);

    min_heapify(&heap, N);

    printf("ordered: \n");
    print_heap(&heap);

    printf("min: %f\n\n", heap_find_min(&heap).min_edge);

    heap_deletemin(&heap);

    printf("deletemin: \n");
    print_heap(&heap);

    Node n = {.min_edge = 2.0, .id = heap.n + 1};

    heap_insert(&heap, n);

    printf("\ninsert: \n");
    print_heap(&heap);

    /*for (int i = 0; i < N; i++) {
        printf("min: %f\n\n", heap_find_min(&heap).min_edge);
        heap_deletemin(&heap);
        printHeap(&heap);
    }
*/
    free_heap(&heap);

}