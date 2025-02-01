#include "dsu.h"


/// Make a new set
void DisjointSet::makeSet(Vertex *vertex) {
    parent[vertex] = vertex;
    rank[vertex] = 0;
}


/// Find vertex's parent
Vertex* DisjointSet::find(Vertex *vertex) {
    return (parent[vertex] == vertex) ? vertex : parent[vertex] = find(parent[vertex]);
}


/// Unite two sets
void DisjointSet::unite(Vertex *x, Vertex *y) {
    Vertex* xRoot = find(x);
    Vertex* yRoot = find(y);

    if (xRoot == yRoot) return; // Already united

    if (rank[xRoot] < rank[yRoot]) parent[xRoot] = yRoot; // (x < y) yRoot becomes parent of xRoot
    else {
        parent[yRoot] = xRoot; // (x >= y) xRoot becomes parent of yRoot
        if (rank[xRoot] == rank[yRoot]) rank[xRoot]++; // (x == y) xRoot's rank increases by 1
    }
}