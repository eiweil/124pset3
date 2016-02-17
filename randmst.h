typedef struct node {
    long id;
    float x1;
    float x2;
    float x3;
    float x4;
} Node;

/*
typedef struct node3D {
    long id;
    float x;
    float y;
    float z;
} Node3D;

typedef struct node4D {
    long id;
    float w;
    float x;
    float y;
    float z;
} Node4D;
*/

typedef struct edge {
    long node1;
    long node2;
    float dist;
} Edge;

struct Graph {
    Node* head;
    long n;
};