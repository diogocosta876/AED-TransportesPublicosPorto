//
// Created by diogo on 17/01/2022.
//

#ifndef AED_TRANSPORTESPUBLICOSPORTO_LOADDATA_H
#define AED_TRANSPORTESPUBLICOSPORTO_LOADDATA_H

#include "graph.h"
#include "Line.h"
#include "Stop.h"
#include "vector"

class LoadData {
    vector<Stop> stops;

public:
    LoadData();
    void displayStops();

private:
    void loadStops();
    void loadLines();

};


#endif //AED_TRANSPORTESPUBLICOSPORTO_LOADDATA_H
