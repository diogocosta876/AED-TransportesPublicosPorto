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
    double walking_distance;

public:
    explicit LoadData(double walking_distance = 0.5);
    Graph& getGraph();
    vector<Stop*>& getStops();
    vector<Line*>& getLines();
    map<string, int>& getStopCodes();
    void setWalkingDistance(double walkingDistance);
    double getWalkingDistance() const;
    void debug_displayStops() const;
    void debug_displayLines() const;
    void debug_displayStopCodes() const;
    void debug_displayEdges() const;
private:
    void loadStops();
    void loadLines();
    void buildGraph();
    static double getDistance(const Stop& a, const Stop& b);

};


#endif //AED_TRANSPORTESPUBLICOSPORTO_LOADDATA_H
