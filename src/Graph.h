// AED 2021/2022 - Aula Pratica 09
// Pedro Ribeiro (DCC/FCUP) [03/01/2022]

#ifndef AED_TRANSPORTESPUBLICOSPORTO_GRAPH_H_
#define AED_TRANSPORTESPUBLICOSPORTO_GRAPH_H_

#include "Stop.h"
#include <utility>
#include <vector>
#include <list>
#include <queue>
#include <iostream>
#include <algorithm>
#include "cmath"

using namespace std;

class Graph {
    struct Edge {
        int dest;   // Destination node
        double weight; // An integer weight
        string lineCode;
    };

    struct Node {
        Stop stop;
        list<Edge> adj; // The list of outgoing edges (to adjacent nodes)
        bool visited;   // Has the node been visited on a search?
        Node(Stop stop): stop(std::move(stop)){}
    };

    int n;              // Graph size (vertices are numbered from 1 to n)
    vector<Node> nodes; // The list of nodes being represented

public:
    explicit Graph(const vector<Stop*>& stops);
    void addEdge(int src, int dest, string lineCode);
    void dfs(int v);
    void bfs(int v);
    int outDegree(int v);
    int connectedComponents();
    int giantComponent();
    list<int> topologicalSorting();
    int distance(int a, int b);
    int diameter();
    bool hasCycle();
    static double haversine(double lat1, double lon1, double lat2, double lon2);
    void debug_displayEdges() const;
};

#endif
