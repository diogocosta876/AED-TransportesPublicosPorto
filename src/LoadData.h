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
    map<string, int> stopCodes;
public:
    LoadData();
    const Graph &getGraph() const;
    const vector<Stop*>& getStops() const;
    const vector<Line*>& getLines() const;
    const map<string, int>& getStopCodes() const;
    void displayStops() const;
    void displayLines() const;
    void displayStopCodes() const;
    void debug_displayEdges() const;
private:
    void loadStops();
    void loadLines();
    void buildGraph();

};


#endif //AED_TRANSPORTESPUBLICOSPORTO_LOADDATA_H
