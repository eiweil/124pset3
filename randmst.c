#include <pcg_basic.h>
#include <binheap.h>


// calculates distance between nodes (of any dimension)
float dist(Node* node1, Node* node2) {

    float dim1 = pow(node1->x1 - node2->x1, 2);
    float dim2 = pow(node1->x2 - node2->x2, 2);
    float dim3 = pow(node1->x3 - node2->x3, 2);
    float dim4 = pow(node1->x4 - node2->x4, 2);

    // for lower dimensions, higher-dimensioned terms are 0
    return sqrt(dim1 + dim2 + dim3 + dim4);
}

// find index for the distance between nodes a and b
// in array corresponding to an upper-triangular matrix
int get_index(int a, int b, int n) {

    // find min of two ids
    int min, max;
    if (a <= b) {
        min = a;
        max = b;
    }
    else {
        min = b;
        max = a;
    }

    if (min == 0) 
        return max - 1;

    int row = n * min + -(min * min + min) / 2;
    int col = max - min - 1;
    return (row + col);
}

int main(int argc, char *argv[]) {

    char* usage = "randmst usage: randmst 0 numpoints numtrials dimension";

    if (argc != 5) {
        printf("%s\n", usage);
        exit(0);
    }

    char* end;

    int n = strtol(argv[2], &end, 10);
    int trials = strtol(argv[3], &end, 10);
    int dim = strtol(argv[4], &end, 10);

    if (dim == 1 || dim < 0 || dim > 4) {
        printf("%s\n", "dimension must be 0 or between 2 and 4, inclusive");
        exit(0);
    }

    // adjacency matrix
    float A[n*n];

    // array of nodes
    Node* nodes = calloc(n, sizeof(Node));

    pcg32_random_t rng1;
    pcg32_srandom_r(&rng1, time(NULL), (intptr_t)&rng1);

    float total = 0;

    for (int trial = 0; trial < trials; trial++) {

        float tree_weight = 0;
        float weight;

        // weights of edges chosen uniformly at random on [0,1]
        if (dim == 0) {

            int index;

            //for (int i = 0; i < n * (n-1) / 2; i++) {
            for (int j = 0; j < n - 2; j++) {

                // start with first node in partial MST
                if (j == 0) {
                    for (int k = j + 1; k < n - 1; k++) {
                        weight = (float) pcg32_random_r(&rng1) / UINT32_MAX;
                        index = get_index(j, k, n);
                        A[index] = weight;
                        printf("%f   ", weight);
                        (nodes + k)->min_edge = weight;
                    }
                }
                else {
                    for (int k = j + 1; k < n - 1; k++) {
                        weight = (float) pcg32_random_r(&rng1) / UINT32_MAX;
                        index = get_index(j, k, n);
                        A[index] = weight;
                        printf("%f   ", weight);
                    }
                }
                
                printf("\n");
            }
        }

        // weights of edges are Euclidean distances between connected vertices
        else {
            for (int i = 0; i < n; i++) {
                Node* newnode = nodes + i;
                newnode->id = i;
                if (dim >= 2) {
                    newnode->x1 = (float) pcg32_random_r(&rng1) / UINT32_MAX;
                    newnode->x2 = (float) pcg32_random_r(&rng1) / UINT32_MAX;
                }
                if (dim >= 3) {
                    newnode->x3 = (float) pcg32_random_r(&rng1) / UINT32_MAX;
                }
                if (dim == 4) {
                    newnode->x4 = (float) pcg32_random_r(&rng1) / UINT32_MAX;
                }
            }

            // create adjacency matrix
            for (int j = 0; j < n; j++) {

                // start with first node in partial MST
                if (j == 0) {
                    for (int k = 0; k < n; k++) {
                        weight = dist(nodes + j, nodes + k);
                        A[n*j + k] = weight;
                        (nodes + k)->min_edge = weight;
                        printf("%f   ", weight);
                    }
                }
                else {
                    for (int k = 0; k < n; k++) {
                        weight = dist(nodes + j, nodes + k);
                        A[n*j + k] = weight;
                        printf("%f   ", weight);
                    }
                }
                
                printf("\n");
            }

        }

        // create heap of vertices (excluding first; it's already in MST)
        struct Heap heap;
        heap_init(&heap, nodes + 1, n - 1);
        min_heapify(heap.nodes, heap.n);

        // Prim's Algorithm

        /*while (heap.n) {
            Node next_node = heap_find_min(&heap);


            float min_edge = next_node.min_edge;
            tree_weight += min_edge;

            heap_deletemin(&heap);

            // update min-edge-weights if needed
            float new_weight;
            if (new_weight < min_edge)

        }*/

        total += tree_weight;
        printf("done with trial %d, MST weight: %f\n\n", trial, tree_weight);

    }

    float average = total / trials;
    printf("average weight of MST over %d trials: %f", trials, average);


}