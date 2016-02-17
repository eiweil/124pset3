


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>

#include <pcg_basic.h>
#include <randmst.h>


// calculates distance between nodes (of any dimension)
float dist(Node* node1, Node* node2) {

    float dim1 = pow(node1->x1 - node2->x1, 2);
    float dim2 = pow(node1->x2 - node2->x2, 2);
    float dim3 = pow(node1->x3 - node2->x3, 2);
    float dim4 = pow(node1->x4 - node2->x4, 2);

    // for lower dimensions, higher-dimensioned terms are 0
    return sqrt(dim1 + dim2 + dim3 + dim4);
}

int main(int argc, char *argv[]) {

    char* usage = "randmst usage: randmst 0 numpoints numtrials dimension";

    //if (argc != 5) {
    //    printf("%s\n", usage);
    //}

    char* end;

    long n = strtol(argv[2], &end, 10);
    long trials = strtol(argv[3], &end, 10);
    int dim = strtol(argv[4], &end, 10);

    // adjacency matrix
    float A[n*n];

    // array of nodes
    Node* M[n];

    pcg32_random_t rng1;
    pcg32_srandom_r(&rng1, time(NULL), (intptr_t)&rng1);
    
    for (int trial; trial < trials; trial++) {

        // weights of edges chosen uniformly at random on [0,1]
        if (dim == 0) {
            for (int i = 0; i < n * n; i++) {
                A[i] = (float) pcg32_random_r(&rng1) / UINT32_MAX;
            }
        }
        // weights of edges are Euclidean distances between connected vertices
        else {
            for (int i = 0; i < n; i++) {
                Node* newnode = (Node*) calloc(1, sizeof(Node));
                newnode->id = i;
                if (dim == 2) {
                    newnode->x1 = (float) pcg32_random_r(&rng1) / UINT32_MAX;
                    newnode->x2 = (float) pcg32_random_r(&rng1) / UINT32_MAX;
                }
                else if (dim == 3) {
                    newnode->x3 = (float) pcg32_random_r(&rng1) / UINT32_MAX;
                }
                else if (dim == 4) {
                    newnode->x4 = (float) pcg32_random_r(&rng1) / UINT32_MAX;
                }
                M[i] = newnode;
            }

            // create adjacency matrix
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    float res = dist(M[j], M[k]);
                    A[n*j + k] = res;
                    printf("%f   ", res);
                }
                printf("\n");
            }

            for (int i = 0; i < n; i++) {
                free(M[i]);
            }
        }

        printf("done with trial %d\n\n", trial);

    }

    // find MST

}