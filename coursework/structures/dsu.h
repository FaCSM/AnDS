#ifndef DSU_H
#define DSU_H


#include "graph.h"
#include <map>


class DisjointSet {
private:
    std::map<Vertex*, Vertex*> parent = {}; // Map of {vertex : parent}
    std::map<Vertex*, int> rank = {};       // Map of {vertex : rank}

public:
    void makeSet(Vertex*);
    Vertex* find(Vertex*);
    void unite(Vertex*, Vertex*);
};


#endif //DSU_H
