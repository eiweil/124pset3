#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>


typedef struct node {
    unsigned long id;
    float min_edge;
    float x1;
    float x2;
    float x3;
    float x4;
} Node;

typedef struct edge {
    unsigned long node1;
    unsigned long node2;
    float dist;
} Edge;

struct Tree {
    Node* head;
    long n;
};