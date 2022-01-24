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
#include <set>

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

    int n;              // Graph size (vertices are numbered from 0 to n-1)
    vector<Node> nodes; // The list of nodes being represented

public:
    explicit Graph(const vector<Stop*>& stops);
    void addEdge(int src, int dest, string  = "");

    //Dijkstra in O(|E| log |V|) using only STL and sets, to determine the shortest path
    pair<pair<vector<int>, double>, vector<string>> dijkstra_util(int a, int b);
    void dijkstra(int s, vector<double>& dist, vector<int>& pred, vector<vector<string>>& lines);

    // Breadth-First Search to determine the path that crosses less stops
    vector<int> bfsPathSearch(int src, int dest);

    void determineLessLineChangesPath_util(int u, int d, bool visited[], vector<pair<int, string>>&path, vector<vector<pair<int, string>>>& path_store, string line);
    void determineLessZonesCrossedPath_util(int u, int d, bool *visited, vector<pair<int, string>> &path, vector<vector<pair<int, string>>> &path_store, string zone);
    vector<pair<int, string>> determineLessLineChangesPath(int s, int d);
    vector<pair<int, string>> determineLessZonesCrossedPath(int s, int d);

    double determineDistanceTraveled(const vector<int>& path);
    list<string> determineLineChanges(vector<int> path);
    static double haversine(double lat1, double lon1, double lat2, double lon2);

    void debug_displayEdges() const;
};

#endif
