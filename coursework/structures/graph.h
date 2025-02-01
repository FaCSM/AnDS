#ifndef GRAPH_H
#define GRAPH_H


#include <regex>
#include <map>
#include <vector>
#include <stack>
#include <queue>


class Vertex {
    friend class Graph;

private:
    char _name;
    std::map<Vertex*, int> edges;

public:
    explicit Vertex(char);
    void setEdge(Vertex*, int);
    [[nodiscard]] char getName() const;
    friend std::ostream& operator<< (std::ostream&, const Vertex&);
};


class Edge {
    friend class Graph;

private:
    int weight;
    Vertex *u;
    Vertex *v;

public:
    Edge(int, Vertex*, Vertex*);
    [[nodiscard]] int getWeight() const;
    Vertex * getU();
    Vertex * getV();
    friend std::ostream& operator<< (std::ostream&, Edge&);
    bool operator< (const Edge&) const;
};


class Graph {
private:
    std::vector<Vertex*> vertices;

public:
    Graph();
    Graph(const std::vector<char>&, const std::vector<std::vector<int>>&);

    std::vector<Vertex*> depthFirstSearch();
    std::vector<Vertex*> breadthFirstSearch();

    std::vector<Edge> getSortedByWeight();
    std::vector<Edge> getMST();
};


#endif //GRAPH_H
