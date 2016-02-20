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
    int node1;
    int node2;
    float dist;
} Edge;

struct Tree {
    Node* head;
    int n;
};

float dist(Node* node1, Node* node2);