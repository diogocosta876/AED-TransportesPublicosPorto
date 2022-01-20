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

// Depth-First Search: modified implementation to get the shortest path in unweighted graphs
void Graph::dfs(int v) {
    cout << v << " "; // show node order
    nodes[v].visited = true;
    for (auto e : nodes[v].adj) {
        int w = e.dest;
        if (!nodes[w].visited)
            dfs(w);
    }
}

// Breadth-First Search
vector<int> Graph::bfsPathSearch(int src, int dest) {
    vector<int> path;
    int predecessor[n]; int dist[n];
    for (int i=0; i<n; i++){
        nodes[i].visited = false;
        dist[i] = INT_MAX;
        predecessor[i] = -1;
    }
    queue<int> q; // queue of unvisited nodes
    q.push(src);
    nodes[src].visited = true;
    dist[src] = 0;
    while (!q.empty()) { // while there are still unvisited nodes
        int a = q.front(); q.pop();
        for (auto e : nodes[a].adj) {
            int a_dest = e.dest;
            if (!nodes[a_dest].visited) {
                q.push(a_dest);
                dist[a_dest] = dist[a] + 1;
                predecessor[a_dest] = a;
                nodes[a_dest].visited = true;

                //if the destination was reached
                if (a_dest == dest) {
                    int crawl = dest;
                    path.push_back(crawl);
                    while (predecessor[crawl] != -1) {
                        path.push_back(predecessor[crawl]);
                        crawl = predecessor[crawl];
                    }
                    reverse(path.begin(), path.end());
                    return path;
                }
            }
        }
    }
    return path;
}


int Graph::outDegree(int v) {
    if(v < 1 || v > n) return -1;
    else return nodes[v].adj.size();
}


int Graph::connectedComponents() {
    int counter = 0;
    for (int v=1; v<=n; v++) nodes[v].visited = false;
    return 0;
}

int Graph::giantComponent() {
    return 0;
}


list<int> Graph::topologicalSorting() {
    list<int> order;
    return order;
}

int Graph::distance(int a, int b) {
    return 0;
}

int Graph::diameter() {
    return 0;
}

bool Graph::hasCycle() {
    return false;
}

int Graph::dijkstra(int orig, int dest) const{
    //TODO dijkstra
    return 1;
}

list<string> Graph::determineLineChanges(vector<int> path) {
    //TODO ATUALIZAR FAZER MANEIRA RECURSIVA A VER TODAS AS POSSIBILIDADES
    list<string> lines_used;
    string current_line = ""; //line being used
    bool found_same_line = false;
    for (int i = 0; i<path.size();i++){
        found_same_line = false;
        //find edge that connects stopID and stopID+1 from path, then see if the line is alreay registed
        auto edges = nodes[path[i]].adj;
        for (const Edge& edge: edges){
            if (edge.dest == path[i+1] && edge.lineCode == current_line){
                found_same_line = true;
                break;
            }
        }
        if (!found_same_line){
            for (const Edge& edge: nodes[path[i]].adj) {
                if (edge.dest == path[i+1]) {
                    current_line = edge.lineCode;
                    lines_used.push_back(edge.lineCode);
                }
            }
        }
    }
    return lines_used;
}

double Graph::determineDistanceTraveled(const vector<int>& path){
    double distance;
    for (int i=0; i<path.size()-1;i++){
        auto node1 = nodes[path[i]].stop;
        auto node2 = nodes[path[i+1]].stop;
        distance+=haversine(node1.getLatitude(), node1.getLongitude(), node2.getLatitude(), node2.getLongitude());
    }
    return distance;
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

