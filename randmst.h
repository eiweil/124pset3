#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>


typedef struct node {
    int id;
    float min_edge;
    float x1;
    float x2;
    float x3;
    float x4;
} Node;

typedef struct edge {
    int node;
    struct edge* next;
    float weight;
} Edge;

float dist(Node* node1, Node* node2);

void add_edge (Edge** V, Edge* e, int id);

void print_list(Edge** V, int n);