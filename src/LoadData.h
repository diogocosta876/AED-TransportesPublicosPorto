//
// Created by diogo on 17/01/2022.
//

#ifndef AED_TRANSPORTESPUBLICOSPORTO_LOADDATA_H
#define AED_TRANSPORTESPUBLICOSPORTO_LOADDATA_H

#include "Graph.h"
#include "Line.h"
#include "Stop.h"
#include "vector"
#include <iterator>
#include <map>

class LoadData {
    Graph graph;
    vector<Stop*> stops;
    vector<Line*> lines;
    map<string, int> stopCodes; //Hashtable que associa o código de uma paragem ao seu id
    double walking_distance;

public:
    /**
     * Construtor da classe
     * @param walking_distance inteiro que define a distância máxima entre paragens para poderem
     * ser conectadas no grafo simulando caminho pedestre
     */
    explicit LoadData(double walking_distance = 0.5);
    /** Getter do atributo graph */
    Graph& getGraph();
    /** Getter do atributo stops */
    vector<Stop*>& getStops();
    /** Getter do atributo lines */
    vector<Line*>& getLines();
    /** Getter do atributo stopCodes */
    map<string, int>& getStopCodes();
    /** Setter do método walking_distance */
    void setWalkingDistance(double walkingDistance);
    /** Getter do atributo walking_distance */
    double getWalkingDistance() const;
    /** Método de debug -> mostra no terminal algumas paragens do dataset */
    void debug_displayStops() const;
    /** Método de debug -> mostra no terminal algumas linhas do dataset */
    void debug_displayLines() const;
    /** Método de debug -> mostra no terminal alguns elementos do atributo stopCodes */
    void debug_displayStopCodes() const;
    /** Método de debug -> mostra no terminal algumas edges */
    void debug_displayEdges() const;
private:
    /**
     * Método void que dá parse ao dataset e introduz as paragens nos atributos
     * stopCodes e stops
     */
    void loadStops();

    /**
     * Método void que dá parse ao dataset e introduz as linhas no atributo lines
    */
    void loadLines();

    /**
     * Método void que utiliza os atributos lines e stops para construir o grafo e as respetivas edges.
     * Cria também edges adicionais se a distância entre quaiquer duas nodes
     * se verificar inferior que o atributo walking_distrance
    */
    void buildGraph();

    /**
     * Método static que calcula a distância entre duas paragens
     * @return double representativo da distância em kilómetros
    */
    static double getDistance(const Stop& a, const Stop& b);

};


#endif //AED_TRANSPORTESPUBLICOSPORTO_LOADDATA_H
