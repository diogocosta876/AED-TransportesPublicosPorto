#include "Line.h"
using namespace std;


Line::Line(const string& code, const string& name) {
    this->code = code;
    this->name = name;
}

void Line::addStop(Stop* stop) {
    stops.push_back(stop);
}


string Line::getCode() const {
    return code;
}
string Line::getName() const {
    return name;
}

const vector<Stop*> &Line::getStops() const {
    return stops;
}

