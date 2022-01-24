#include <fstream>
#include "LoadData.h"

using namespace std;

LoadData::LoadData(double walking_distance): graph(vector<Stop*>{}) {
    loadStops();
    loadLines();
    buildGraph();
    this->walking_distance = walking_distance;
}

void LoadData::loadStops() {
    string textLine;
    ifstream MyReadFile("../data/Stops.csv");

    //Load Stops into a vector to then build the graph in buildGraph()
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
        aux = textLine = textLine.substr(textLine.find(',')+1, textLine.size());
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

    // load lines into a vector to then build the graph in buildGraph()
    string code, name;
    getline(MyReadFile, textLine);
    while (getline (MyReadFile, textLine)) {
        code = textLine.substr(0, textLine.find(','));
        name = textLine.substr(textLine.find('-') + 2, textLine.size());
        textLine = textLine.substr(textLine.find(',')+1, textLine.size());
        lines.emplace_back(new Line(code, name));
    }
    for (Line* line: lines){
        string textLine2, stops_count;
        ifstream MyReadFile2("../data/Line_" + line->getCode() + "_0.csv");
        getline (MyReadFile2, stops_count);
        for (int i = 0; i < stoi(stops_count) ; ++i) {
            getline (MyReadFile2, textLine2);
            Stop* stop = stops[stopCodes.find(textLine2)->second];
            line->addStop(stop);
        }
    }
}

void LoadData::buildGraph() {
    graph = Graph(stops);

    //Use Lines and Stops vectors to build the graph
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
        }
    }

    // Add edges based on the walking_distance variable
    for(pair<string, int> stop1_data: stopCodes){
        for(pair<string, int> stop2_data: stopCodes){
            if (stop1_data.second != stop2_data.second && getDistance(*stops[stop1_data.second], *stops[stop2_data.second]) <= walking_distance){
                graph.addEdge(stop1_data.second, stop2_data.second, "WALK");
                graph.addEdge(stop2_data.second, stop1_data.second, "WALK");
            }
        }
    }
}

double LoadData::getDistance(const Stop& a, const Stop& b) {
    return Graph::haversine(a.getLatitude(), a.getLongitude(), b.getLatitude(), b.getLongitude());
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

double LoadData::getWalkingDistance() const {
    return walking_distance;
}

void LoadData::setWalkingDistance(double walkingDistance) {
    walking_distance = walkingDistance;
}

void LoadData::debug_displayStops() const {
    cout << "Examples Stops:\n";
    for (int i= 0; i<5; i++){
        cout << stops[i]->getCode() << endl;
    }
}
void LoadData::debug_displayLines() const {
    cout << "Examples lines:\n";
    for (int i=0;i<5;i++){
        cout << lines[i]->getCode() << endl;
    }
}

void LoadData::debug_displayStopCodes() const {
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

