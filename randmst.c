#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <randmst.h>

#define N 10

//int dimension;

float A[N*N];
Node* M[N];

// calculates distance between nodes
float dist(Node* node1, Node* node2) {

    float dim1 = pow(node1->x1 - node2->x1, 2);
    float dim2 = pow(node1->x2 - node2->x2, 2);
    float dim3 = pow(node1->x3 - node2->x3, 2);
    float dim4 = pow(node1->x4 - node2->x4, 2);

    // for lower dimensions, higher-dimensioned terms are 0
    return sqrt(dim1 + dim2 + dim3 + dim4);
}

int main() {
    
    srand(time(NULL));

    // initialize nodes (uniformly pseudorandomly)
    for (int i = 0; i < N; i++) {
        Node* newnode = (Node*) calloc(1, sizeof(Node));
        newnode->id = i;
        newnode->x1 = (float) rand() / RAND_MAX;
        newnode->x2 = (float) rand() / RAND_MAX;
        M[i] = newnode;
    }

    // create adjacency matrix
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
            float res = dist(M[j], M[k]);
            A[N*j + k] = res;
            printf("dist for nodes %d, %d: %f\n", j, k, res);
        }
    }

    //printf("%f\n", dist(node1, node2));

    for (int i = 0; i < N; i++) {
        free(M[i]);
    }
}