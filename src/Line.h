#ifndef AED_TRANSPORTESPUBLICOSPORTO_LINE_H
#define AED_TRANSPORTESPUBLICOSPORTO_LINE_H

#include "Stop.h"
#include <string>
#include <vector>

class Line {
    string code;
    string name;
    bool hasDir;
    vector<Stop> stops;
public:
    Line(const string& code, const string& name);
    string getCode() const;
    string getName() const;
    bool hasDirection() const;
};


#endif //AED_TRANSPORTESPUBLICOSPORTO_LINE_H
