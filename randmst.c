


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

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
    int dim = strtol(argv[4], &end, 10);

    float A[n*n];
    Node* M[n];
    
    srand(time(NULL));

    // initialize nodes (uniformly pseudorandomly)
    for (int i = 0; i < n; i++) {
        Node* newnode = (Node*) calloc(1, sizeof(Node));
        newnode->id = i;
        if (dim == 2) {
            newnode->x1 = (float) rand() / RAND_MAX;
            newnode->x2 = (float) rand() / RAND_MAX;
        }
        else if (dim == 3) {
            newnode->x3 = (float) rand() / RAND_MAX;
        }
        else if (dim == 4) {
            newnode->x4 = (float) rand() / RAND_MAX;
        }
        //else {
            // random real-weighted edges [0,1]
        //}
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

    //printf("%f\n", dist(node1, node2));

    for (int i = 0; i < n; i++) {
        free(M[i]);
    }
}