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
        explicit Node(Stop stop): stop(std::move(stop)), visited(false){}
    };

    int n;              // Graph size (vertices are numbered from 0 to n-1)
    vector<Node> nodes; // The list of nodes being represented

public:
    /**
     * Construtor da classe
     * @param stops vetor de Stop pointers
     */
    explicit Graph(const vector<Stop*>& stops);
    /**
     * Método void que adiciona uma edge ao grafo, dados os índices de duas nodes. Complexidade temporal O(1)
     * @param src id de node
     * @param dest id de node
     * @param linecode código de linha
     */
    void addEdge(int src, int dest, string linecode = "");

    /**
     * Método auxiliar à funcção dijkstra()
     * @see dijkstra
     * @return pair de pair de vetor de inteiros (ids de node) e double(distancia percorrida)
     * e vetor de strings (linhas percorridas)
     */
    pair<pair<vector<int>, double>, vector<string>> dijkstra_util(int a, int b);
    /**
     * Dijkstra de complexidade temporal O(|E| log |V|) usando apenas STL e Sets,
     * para determinar o caminho mais curto
     * @param a id de node inicial
     * @param b id de node de destino
     */
    void dijkstra(int s, vector<double>& dist, vector<int>& pred, vector<vector<string>>& lines);

    /**
     * Pesquisa Breadth-First de complexidade temporal O(|E|+|V|) para determinar
     * o caminho que percorre menos nodes (paragens)
     * @param a id de node inicial
     * @param b id de node de destino
     * @return vetor de inteiros representando as ids das nodes percorridas.
     */
    vector<int> bfsPathSearch(int src, int dest);

    /**
     * Pesquisa DFS de complexidade temporal O(V^V) que itera todos os caminhos possíveis
     * da node de origem até à node de destino e guarda-os em path_store (guarda zonas percorridas)
     * @param a id de node inicial
     * @param b id de node de destino
    */
    void determineLessLineChangesPath_util(int u, int d, bool visited[], vector<pair<int, string>>path, vector<vector<pair<int, string>>>& path_store, string line);

    /**
     * Pesquisa DFS de complexidade temporal O(V^V) que itera todos os caminhos possíveis
     * da node de origem até à node de destino e guarda-os em path_stores (guarda linhas usadas)
     * @param a id de node inicial
     * @param b id de node de destino
    */
    void determineLessZonesCrossedPath_util(int u, int d, bool *visited, vector<pair<int, string>> &path, vector<vector<pair<int, string>>> &path_store, string zone);

    /**
     * Método auxiliar à funcção determineLessLineChangesPath_util() que devolve o percurso que utiliza menos linhas
     * @see determineLessLineChangesPath_util
     * @param a id de node inicial
     * @param b id de node de destino
     * @return vetor de pares de inteiros(ids de node) e strings(linhas)
    */
    vector<pair<int, string>> determineLessLineChangesPath(int s, int d);

    /**
     * Método auxiliar à funcção determineLessZonesCrossedPath_util() que devolve o percurso que atravessa menos zonas
     * @see determineLessLessZonesCrossedPath
     * @param a id de node inicial
     * @param b id de node de destino
     * @return vetor de pares de inteiros(ids de node) e strings(zonas)
    */
    vector<pair<int, string>> determineLessZonesCrossedPath(int s, int d);

    /**
     * Método que retorna a distância percorrida através do percurso tomado
     * @param path vetor de inteiros (ids de nodes)
     * @return double (distância percorrida)
    */
    double determineDistanceTraveled(const vector<int>& path);
    //list<string> determineLineChanges(vector<int> path);
    /**
    * Método estático que retorna a distância entre duas coordenadas longitudinais e latitudinais
    * @param lat1 double
    * @param lon1 double
    * @param lat2 double
    * @param lon2 double
    * @return double (distância)
   */
    static double haversine(double lat1, double lon1, double lat2, double lon2);

    /** Método de debug -> mostra no terminal algumas edges */
    void debug_displayEdges() const;
};

#endif
