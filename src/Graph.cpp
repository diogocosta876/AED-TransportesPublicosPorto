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

pair<pair<vector<int>, int>, vector<string>> Graph::dijkstra_path(int a, int b) {
    vector<double> dist;
    vector<int> pred;
    vector<vector<string>> lines;
    pair<pair<vector<int>, int>, vector<string>> mypair;
    dijkstra(a, dist, pred, lines);
    vector<int> path;
    mypair.first.first = path;
    mypair.first.second = -1;
    mypair.second = lines[b];
    if (dist[b] == INT_MAX) return mypair;
    path.push_back(b);
    int v = b;
    while (v != a) {
        v = pred[v];
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    mypair.first.first = path;
    mypair.first.second = dist[b];
    mypair.second = lines[b];
    return mypair;
}

vector<pair<int, string>> Graph::determineLessLineChangesPath(int s, int d)
{
    // Mark all the vertices as not visited
    bool* visited = new bool[n];

    // Create an array to store paths
    vector<pair<int, string>> path;
    vector<vector<pair<int, string>>> path_store;

    // Initialize all vertices as not visited
    for (int i = 0; i < n; i++)
        visited[i] = false;

    // Call the recursive helper function to print all paths
    printAllPathsUtil(s, d, visited, path, path_store, "");

    int min = INT_MAX;
    vector<pair<int, string>> min_path;
    vector<string> line_counter;
    for (vector<pair<int, string>> path: path_store){
        line_counter.clear();
        for (pair<int, string> stop: path){
            if (find(line_counter.begin(), line_counter.end(), stop.second) == line_counter.end())
                line_counter.push_back(stop.second);
        }
        if (line_counter.size() < min){
            min = line_counter.size();
            min_path = path;
        }
        cout << endl << "LINE COUNTER: ";
        for (auto st: line_counter) cout << st << " ";
    }
    return min_path;

}

// A recursive function to print all paths from 'u' to 'd'.
// visited[] keeps track of vertices in current path.
// path[] stores actual vertices and path_index is current
// index in path[]
void Graph::printAllPathsUtil(int u, int d, bool visited[], vector<pair<int, string>>&path, vector<vector<pair<int, string>>>& path_store, string line)
{
    // Mark the current node and store it in path[]
    visited[u] = true;
    pair<int, string> mypair;
    mypair.first = u;
    mypair.second = line;
    path.push_back(mypair);

    // If current vertex is same as destination, then print
    if (path.size() > 30) return;

    if (u == d) {
        for (int i = 0; i < path.size(); i++)
            cout << path[i].first << " line:" << path[i].second << "  ";
            path_store.push_back(path);
        cout << endl;
    }

    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        list<int>::iterator i; queue<int> q;
        for (auto edge: nodes[u].adj)
            if (!visited[edge.dest]) {
                printAllPathsUtil(edge.dest, d, visited, path, path_store, edge.lineCode);
            }
    }

    // Remove current vertex from path[] and mark it as unvisited
    visited[u] = false;
}



//Dijkstra in O(|E| log |V|) using only STL and sets
void Graph::dijkstra(int s, vector<double>& dist, vector<int>& pred, vector<vector<string>>& lines) {
    set<pair<int, int>> q;
    for (int v=0; v<n; v++) {
        dist.push_back(INT_MAX);
        pred.push_back(-1);
        lines.push_back(vector<string> {""});
        q.insert({INT_MAX, v});
        nodes[v].visited = false;
    }
    dist[s] = 0;
    q.erase({INT_MAX, s});
    q.insert({0, s});
    pred[s] = s;
    while (q.size()>0) {
        int u = q.begin()->second;
        q.erase(q.begin());
        cout << "Node " << nodes[u].stop.getCode() << " dist = " << dist[u] << " lines:"; for (auto line: lines[u]) cout << line << " ";
        cout << "\n";
        nodes[u].visited = true;
        for (auto current_edge : nodes[u].adj) {
            int next = current_edge.dest;
            if (!nodes[next].visited && dist[u] + current_edge.weight < dist[next]) {
                q.erase({dist[next], next});
                dist[next] = dist[u] + current_edge.weight;
                pred[next] = u;
                lines[next] = lines[u]; lines[next].push_back(current_edge.lineCode);
                q.insert({dist[next], next});
            }
        }
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

