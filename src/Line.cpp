#include "Line.h"
using namespace std;


Line::Line(const string& code, const string& name) {
    this->code = code;
    this->name = name;
}

string Line::getCode() const {
    return code;
}
string Line::getName() const {
    return name;
}

bool Line::hasDirection() const {
    return hasDir;
}

