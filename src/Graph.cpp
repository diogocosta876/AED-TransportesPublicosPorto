// AED 2021/2022 - Aula Pratica 09
// Pedro Ribeiro (DCC/FCUP) [03/01/2022]

#include "Graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(const vector<Stop*>& stops) {
    n = stops.size();
    for(Stop* stop : stops){
        nodes.emplace_back(*stop);
    }
}

void Graph::addEdge(int src, int dest, string lineCode) {
    if (src<0 || src>n || dest<0 || dest>n) return;
    Node node1 = nodes[src]; Node node2 = nodes[dest];
    double weight = haversine(node1.stop.getLatitude(), node1.stop.getLongitude(), node2.stop.getLatitude(), node2.stop.getLongitude());
    nodes[src].adj.push_back({dest, weight, lineCode});
}

// Depth-First Search: example implementation
void Graph::dfs(int v) {
    cout << v << " "; // show node order
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}

// Depth-First Search: example implementation
void Graph::bfs(int v) {
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    queue<int> q; // queue of unvisited nodes
    q.push(v);
    nodes[v].visited = true;
    while (!q.empty()) { // while there are still unvisited nodes
        int u = q.front(); q.pop();
        cout << u << " "; // show node order
        for (auto e : nodes[u].adj) {
            int w = e.dest;
            if (!nodes[w].visited) {
                q.push(w);
                nodes[w].visited = true;
            }
        }
    }
}

// ----------------------------------------------------------
// Exercicio 1: Introdução a uma classe simplificada de grafos
// ----------------------------------------------------------

// ..............................
// a) Contando diferentes somas de pares
// TODO
int Graph::outDegree(int v) {
    if(v < 1 || v > n) return -1;
    else return nodes[v].adj.size();
}

// ----------------------------------------------------------
// Exercicio 2: Componentes conexos
// ----------------------------------------------------------

// ..............................
// a) Contando componentes conexos
// TODO
int Graph::connectedComponents() {
    int counter = 0;
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    return 0;
}

// ..............................
// b) Componente gigante
// TODO
int Graph::giantComponent() {
    return 0;
}


// ----------------------------------------------------------
// Exercicio 3: Ordenacao topologica
// ----------------------------------------------------------
// TODO
list<int> Graph::topologicalSorting() {
    list<int> order;
    return order;
}

// ..............................
// a) Distancia entre dois nos
// TODO
int Graph::distance(int a, int b) {
    return 0;
}

// TODO
int Graph::diameter() {
    return 0;
}

// TODO
bool Graph::hasCycle() {
    return false;
}

int Graph::dijkstra(int orig, int dest) const{
    //TODO dijkstra
}



double Graph::haversine(double lat1, double lon1, double lat2, double lon2){
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}

void Graph::debug_displayEdges() const {
    int counter = 0;
    for (Node node: nodes){
        if (counter > 5) break;
        if (!node.adj.empty()){
            counter++;
            cout << "edges detected\n";
            for (Edge edge: node.adj){
                cout << "dest: " << edge.dest << " distance: " << edge.weight << endl;
            }
        }
    }
}
