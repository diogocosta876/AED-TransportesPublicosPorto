#include "Graph.h"

// Constructor: nr nodes and direction (default: undirected)
Graph::Graph(const vector<Stop*>& stops) {
    n = static_cast<int>(stops.size());
    for(Stop* stop : stops){
        nodes.emplace_back(*stop);
    }
}
void Graph::addEdge(int src, int dest, string lineCode) {
    if (src<0 || src>n || dest<0 || dest>n) return;
    Node node1 = nodes[src]; Node node2 = nodes[dest];
    double weight = haversine(node1.stop.getLatitude(), node1.stop.getLongitude(), node2.stop.getLatitude(), node2.stop.getLongitude());
    nodes[src].adj.push_back({dest, weight, std::move(lineCode)});
}

//Dijkstra in O(|E| log |V|) using only STL and sets, to determine the shortest path
pair<pair<vector<int>, double>, vector<string>> Graph::dijkstra_util(int a, int b) {
    vector<double> dist;
    vector<int> pred;
    vector<vector<string>> lines;
    pair<pair<vector<int>, double>, vector<string>> mypair;
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
    while (!q.empty()) {
        int u = q.begin()->second;
        q.erase(q.begin());
        //cout << "Node " << nodes[u].stop.getCode() << " dist = " << dist[u] << " lines:"; for (auto line: lines[u]) cout << line << " ";
        //cout << "\n";
        nodes[u].visited = true;
        for (const auto& current_edge : nodes[u].adj) {
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

// Breadth-First Search to determine the path that crosses less stops
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
        for (const auto& e : nodes[a].adj) {
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

void Graph::determineLessLineChangesPath_util(int u, int d, bool visited[], vector<pair<int, string>> path, vector<vector<pair<int, string>>>& path_store, string line)
{
    // Mark the current node and store it in path[]
    visited[u] = true;
    pair<int, string> mypair;
    mypair.first = u;
    mypair.second = line;
    path.push_back(mypair);

    // If current vertex is same as destination, then print
    if (path.size() > 6) {
        visited[u] = false;
        return;
    }

    if (u == d) {
        //FOR VISUALIZATION OF THE PATHS ITERATED
        /*for (int i = 0; i < path.size(); i++)
            cout << path[i].first << " line:" << path[i].second << "  ";
        cout << "\n";*/
        path_store.push_back(path);
    }

    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        list<int>::iterator i;
        queue<int> q;
        for (auto edge: nodes[u].adj)
            if (!visited[edge.dest])
                determineLessLineChangesPath_util(edge.dest, d, visited, path, path_store, edge.lineCode);
    }

    // Remove current vertex from path[] and mark it as unvisited
    visited[u] = false;
}
void Graph::determineLessZonesCrossedPath_util(int u, int d, bool visited[], vector<pair<int, string>>&path, vector<vector<pair<int, string>>>& path_store, string zone){

    // Mark the current node and store it in path[]
    visited[u] = true;
    pair<int, string> mypair;
    mypair.first = u;
    mypair.second = zone;
    path.push_back(mypair);

    // If current vertex is same as destination, then print
    if (path.size() > 6) {
        visited[u] = false;
        return;
    }

    if (u == d) {
        path_store.push_back(path);
    }

    else // If current vertex is not destination
    {
        // Recur for all the vertices adjacent to current vertex
        list<int>::iterator i;
        queue<int> q;
        for (auto edge: nodes[u].adj)
            if (!visited[edge.dest])
                determineLessLineChangesPath_util(edge.dest, d, visited, path, path_store, nodes[edge.dest].stop.getZone());
    }

    // Remove current vertex from path[] and mark it as unvisited
    visited[u] = false;
}
vector<pair<int, string>> Graph::determineLessLineChangesPath(int s, int d){
    // Mark all the vertices as not visited
    bool* visited = new bool[n];

    // Create an array to store paths
    vector<pair<int, string>> path;
    vector<vector<pair<int, string>>> path_store;

    // Initialize all vertices as not visited
    for (int i = 0; i < n; i++)
        visited[i] = false;

    // Call the recursive helper function to recursively iterate all paths
    determineLessLineChangesPath_util(s, d, visited, path, path_store, "");

    int min = INT_MAX;
    vector<pair<int, string>> min_path;
    int min_path_size = INT_MAX;
    vector<string> line_counter;
    for (const vector<pair<int, string>>& a_path: path_store){
        line_counter.clear();
        for (const pair<int, string>& stop: a_path){
            if (find(line_counter.begin(), line_counter.end(), stop.second) == line_counter.end())
                line_counter.push_back(stop.second);
        }
        if (line_counter.size() < min || (a_path.size() < min_path_size && line_counter.size() <= min)){
            min = static_cast<int>(line_counter.size());
            min_path = a_path;
            min_path_size = min_path.size();
        }
        //cout << endl << "LINE COUNTER: ";
        //for (auto st: line_counter) cout << st << " ";
    }
    return min_path;
}
vector<pair<int, string>> Graph::determineLessZonesCrossedPath(int s, int d)
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
    determineLessZonesCrossedPath_util(s, d, visited, path, path_store, "");

    int min = INT_MAX;
    vector<pair<int, string>> min_path;
    vector<string> zone_counter;
    for (const vector<pair<int, string>>& a_path: path_store){
        zone_counter.clear();
        for (const pair<int, string>& stop: a_path){
            if (find(zone_counter.begin(), zone_counter.end(), stop.second) == zone_counter.end())
                zone_counter.push_back(stop.second);
        }
        if (zone_counter.size() < min){
            min = static_cast<int>(zone_counter.size());
            min_path = a_path;
        }
        /*cout << endl << "ZONE COUNTER: ";
        for (const auto& st: zone_counter) cout << st << " ";*/
    }
    return min_path;
}

double Graph::determineDistanceTraveled(const vector<int>& path){
    double distance = 0;
    if(!path.empty()) {
        for (int i = 0; i < path.size() - 1; i++) {
            auto node1 = nodes[path[i]].stop;
            auto node2 = nodes[path[i + 1]].stop;
            distance += haversine(node1.getLatitude(), node1.getLongitude(), node2.getLatitude(), node2.getLongitude());
        }
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
    for (const Node& node: nodes){
        if (counter > 5) break;
        if (!node.adj.empty()){
            counter++;
            cout << "edges detected\n";
            for (const Edge& edge: node.adj){
                cout << "dest: " << edge.dest << " distance: " << edge.weight << endl;
            }
        }
    }
}














