#ifndef AED_TRANSPORTESPUBLICOSPORTO_LINE_H
#define AED_TRANSPORTESPUBLICOSPORTO_LINE_H

#include "Stop.h"
#include <string>
#include <vector>

class Line {
    string code;
    string name;
    vector<Stop*> stops;
public:
    Line(const string& code, const string& name);
    void addStop(Stop* stop);
    string getCode() const;
    string getName() const;
    const vector<Stop*> &getStops() const;
};


#endif //AED_TRANSPORTESPUBLICOSPORTO_LINE_H
