#include <fstream>
#include "LoadData.h"

using namespace std;

LoadData::LoadData() {
    loadStops();
    loadLines();
}

void LoadData::displayStops() {
    for (const Stop& stop: stops){
        cout << stop.getCode() << endl;
    }
}

void LoadData::loadStops() {
    string textLine;
    ifstream MyReadFile("../data/Stops.csv");

    string code, name, zone, aux;
    double latitude, longitude;
    getline(MyReadFile, textLine);
    while (getline (MyReadFile, textLine)) {
        code = textLine.substr(0, textLine.find(','));
        textLine = textLine.substr(textLine.find(',') + 1, textLine.size());
        name = textLine.substr(0, textLine.find(','));
        textLine = textLine.substr(textLine.find(',')+1, textLine.size());
        zone = textLine.substr(0, textLine.find(','));
        aux = textLine = textLine.substr(textLine.find(',')+1, textLine.size());;
        latitude = stod(aux.substr(0, textLine.find(',')));
        aux = aux.substr(aux.find(',') + 1, aux.size());
        longitude = stod(aux);
        stops.emplace_back(code, name, zone, latitude, longitude);
    }
}


void LoadData::loadLines() {
    string textLine;
    ifstream MyReadFile("../data/Stops.csv");

    string code, name, zone, aux;
    double latitude, longitude;
    getline(MyReadFile, textLine);
    while (getline (MyReadFile, textLine)) {
        code = textLine.substr(0, textLine.find(','));
        textLine = textLine.substr(textLine.find(',') + 1, textLine.size());
        name = textLine.substr(0, textLine.find(','));
        textLine = textLine.substr(textLine.find(',')+1, textLine.size());
        zone = textLine.substr(0, textLine.find(','));
        aux = textLine = textLine.substr(textLine.find(',')+1, textLine.size());;
        latitude = stod(aux.substr(0, textLine.find(',')));
        aux = aux.substr(aux.find(',') + 1, aux.size());
        longitude = stod(aux);
        stops.emplace_back(code, name, zone, latitude, longitude);
    }
}
