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

// add edge to adjacency list
void add_edge (Edge** V, Edge* e, int id) {
    e->next = V[id];
    V[id] = e;
}

// to print adjacency list (debugging)
void print_list(Edge** V, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", i);
        Edge* curr = *(V + i);
        while (curr != NULL) {
            printf("-%d", curr->node);
            curr = curr->next;
        }
        printf("\n");
    }
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

    // top bound for maximum edge weight in MST
    // nonlinear regression from Mathematica of form (a ^ {b + c log(x)})
    // +0.025 and *1.25 to try and ensure boundedness
    // k_n is of form a+b*c/n^d
    float a, b, c, d;
    if (dim == 0) {
        a = 0.025;
        b = 1.25;
        c = 4.532613;
        d = 0.754872;
    }
    if (dim == 2) {
        a = 0.025;
        b = 1.25;
        c = 2.717475;
        d = 0.494280;
    }
    if (dim == 3) {
        a = 0.025;
        b = 1.25;
        c = 2.100193;
        d = 0.325292;
    }
    if (dim == 4) {
        a = 0.025;
        b = 1.25;
        c = 1.710965;
        d = 0.233472;
    }

    float k_n = a + b * c / pow(n, d);

    k_n = 0.138293;

    printf("k_n = %f\n\n", k_n);

    pcg32_random_t rng1;
    pcg32_srandom_r(&rng1, time(NULL), (intptr_t)&rng1);

    float total = 0;
    float max_edge = 0;

    for (int trial = 0; trial < trials; trial++) {

        // array of nodes
        Node* nodes = calloc(n, sizeof(Node));

        // adjacency list
        Edge** V = calloc(n, sizeof(Edge*));

        float tree_weight = 0;
        float weight;

        if (n == 1)
            continue;
        else if (n == 2) {
            total += (float) pcg32_random_r(&rng1) / UINT32_MAX;
            continue;
        }

        // weights of edges chosen uniformly at random on [0,1]
        if (dim == 0) {

            int index;

            //for (int i = 0; i < n * (n-1) / 2; i++) {
            for (int j = 0; j < n - 1; j++) {

                // start with first node in partial MST
                    for (int k = j + 1; k < n; k++) {
                        weight = (float) pcg32_random_r(&rng1) / UINT32_MAX;
                        
                        if (weight < k_n) {
                            Edge* e1 = (Edge*) malloc(sizeof(Edge));
                            e1->node = k;
                            e1->next = NULL;
                            e1->weight = weight;
                            add_edge(V, e1, j);

                            Edge* e2 = (Edge*) malloc(sizeof(Edge));
                            e2->node = j;
                            e2->next = NULL;
                            e2->weight = weight;
                            add_edge(V, e2, k);
                        }
                        
                        //printf("%f   ", weight);
                        if (j == 0) {
                            (nodes + k)->min_edge = weight;
                            (nodes + k)->id = k;
                        }
                        
                    }
                //}
                /*else {
                    for (int k = j + 1; k < n; k++) {
                        weight = (float) pcg32_random_r(&rng1) / UINT32_MAX;
                        index = get_index(j, k, n);
                        A[index] = weight;
                        
                        if (weight < k_n) {
                            Edge* e = (Edge*) malloc(sizeof(Edge));
                            e->node = k;
                            e->next = NULL;
                            e->weight = weight;
                            add_edge(V, e, j);
                        }
                        
                        //printf("%f   ", weight);
                    }
                }*/

                //printf("\n");
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
                //if (j == 0) {
                for (int k = 0; k < n; k++) {
                    weight = dist(nodes + j, nodes + k);
                    //A[n * j + k] = weight;
                    
                    //if (j != k) {
                    if (weight < k_n && j != k) {
                        Edge* e = (Edge*) malloc(sizeof(Edge));
                        e->node = k;
                        e->next = NULL;
                        e->weight = weight;
                        add_edge(V, e, j);
                    }
                    
                    if (j == 0)
                        (nodes + k)->min_edge = weight;
                    //printf("%f   ", weight);
                }
                //}
                /*else {
                    for (int k = 0; k < n; k++) {
                        weight = dist(nodes + j, nodes + k);
                        A[n*j + k] = weight;
                        //printf("%f   ", weight);
                    }
                }*/
                
                //printf("\n");
            }

        }

        // create heap of vertices (excluding first; it's already in MST)
        struct Heap heap;
        heap_init(&heap, nodes + 1, n - 1);
        //print_heap(&heap);
        heap_number(&heap);
        //print_heap(&heap);
        min_heapify(&heap, heap.n);
        //print_heap(&heap);
        heap.pos[0] = -1;

        //print_heap(&heap);
        
        // Prim's Algorithm

        //print_list(V, n);

        while (heap.n) {
            //print_heap(&heap);
            Node next_node = heap_find_min(&heap);

            float min_edge = next_node.min_edge;
            //printf("added one: %d %f\n", next_node.id, next_node.min_edge);
            tree_weight += min_edge;
            if (min_edge > max_edge)
                max_edge = min_edge;

            heap_deletemin(&heap);

            //printf("after delete\n");
            //print_heap(&heap);
            // update min-edge-weights if needed
            float new_weight;
            Edge* curr = V[next_node.id];
            Edge* prev = V[next_node.id];
            while (curr != NULL) {
                if (in_heap(&heap, curr->node)) { 
                    //printf("%d in heap\n", curr->node);
                    if(curr->weight < 
                        heap.nodes[heap.pos[curr->node]].min_edge) {
                        //printf("changed from %f to %f\n", heap.nodes[heap.pos[curr->node]].min_edge, curr->weight);
                        heap.nodes[heap.pos[curr->node]].min_edge = 
                            curr->weight;

                    }
                    prev = curr;
                }
                /*else {
                    prev->next = curr->next;
                    free(curr);
                    curr = prev->next;
                }*/
                curr = curr->next;
            }
            /*
            for (int i = 1; i < n; i++) {
                if (in_heap(&heap, i)) {

                    int ind;
                    if (dim == 0)
                        ind = get_index(next_node.id, i, n);
                    else
                        ind = n * next_node.id + i;
                    //printf("%d-%d weight: %f vs. %f\n", 
                            //next_node.id, i, A[ind], (heap.nodes[heap.pos[i]]).min_edge);
                    if (A[ind] < (heap.nodes[heap.pos[i]]).min_edge) {
                        //printf("changed value: edge %d-%d to %f\n", next_node.id, i, A[ind]);
                        (heap.nodes[heap.pos[i]]).min_edge = A[ind];
                        //printf("changed: %f\n\n", (heap.nodes[heap.pos[i]]).min_edge);
                    }
                }
            }*/
            if(heap.n > 1)
                min_heapify(&heap, heap.n);
        }

        total += tree_weight;
        //printf("done with trial %d, MST weight: %f\n\n", trial + 1, tree_weight);

        free_heap(&heap);
        free(nodes);
        free(V);
    }

    float average = total / trials;
    float average_edge = average / n;
    printf("average weight of MST over %d trials: %f\n", trials, average);
    printf("average edge weight included in MST over %d trials: %f\n",
            trials, average_edge);
    printf("max edge included in any MST: %f\n", max_edge);

}