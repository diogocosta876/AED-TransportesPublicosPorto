#include <fstream>
#include "LoadData.h"
#include "Graph.h"

using namespace std;

LoadData::LoadData(): graph(vector<Stop*>{}) {
    loadStops();
    loadLines();
    buildGraph();
}

void LoadData::loadStops() {
    string textLine;
    ifstream MyReadFile("../data/Stops.csv");

    string code, name, zone, aux;
    double latitude, longitude;
    int counter = 0;
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
        stops.emplace_back(new Stop(code, name, zone, latitude, longitude));
        stopCodes.insert(pair(code, counter));
        counter++;
    }
}


void LoadData::loadLines() {
    string textLine;
    ifstream MyReadFile("../data/Lines.csv");

    string code, name;
    getline(MyReadFile, textLine);
    while (getline (MyReadFile, textLine)) {
        code = textLine.substr(0, textLine.find(','));
        name = textLine.substr(textLine.find('-') + 2, textLine.size());
        textLine = textLine.substr(textLine.find(',')+1, textLine.size());
        lines.emplace_back(new Line(code, name));
    }
    for (Line* line: lines){
        string textLine, stops_count;
        ifstream MyReadFile("../data/Line_" + line->getCode() + "_0.csv");
        getline (MyReadFile, stops_count);
        for (int i = 0; i < stoi(stops_count) ; ++i) {
            getline (MyReadFile, textLine);
            Stop* stop = stops[stopCodes.find(textLine)->second];
            line->addStop(stop);
        }
    }
}

void LoadData::buildGraph() {
    graph = Graph(stops);

    for(int i=0; i<=1; i++) {
        for (Line* line: lines) {
            string name = line->getCode();
            string textLine;
            ifstream ReadLinePath("../data/line_" + name + "_"+ to_string(i) + ".csv");

            getline(ReadLinePath, textLine);
            int counter = std::stoi(textLine);
            getline(ReadLinePath, textLine);
            int id1 = (stopCodes.find(textLine))->second;
            while (counter > 1) {
                getline(ReadLinePath, textLine);
                int id2 = (stopCodes.find(textLine))->second;
                graph.addEdge(id1, id2, line->getCode());
                id1 = id2;
                counter--;
            }

            getline(ReadLinePath, textLine);
            while (getline(ReadLinePath, textLine)) {

            }
        }
    }
}

void LoadData::displayStops() const {
    cout << "Examples Stops:\n";
    for (int i= 0; i<5; i++){
        cout << stops[i]->getCode() << endl;
    }
}
void LoadData::displayLines() const {
    cout << "Examples lines:\n";
    for (int i=0;i<5;i++){
        cout << lines[i]->getCode() << endl;
    }
}

void LoadData::displayStopCodes() const {
    cout << "Examples StopCodes:\n";
    int counter = 0;
    auto it=stopCodes.begin();
    while(counter<5){
        cout << it->first << " " << it->second << endl;
        counter++;
        it++;
    }
}

void LoadData::debug_displayEdges() const {
    graph.debug_displayEdges();
}

Graph& LoadData::getGraph() {
    return graph;
}

vector<Stop*>& LoadData::getStops() {
    return stops;
}

vector<Line*>& LoadData::getLines() {
    return lines;
}

map<string, int>& LoadData::getStopCodes() {
    return stopCodes;
}
