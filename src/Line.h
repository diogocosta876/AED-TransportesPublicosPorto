#ifndef AED_TRANSPORTESPUBLICOSPORTO_LINE_H
#define AED_TRANSPORTESPUBLICOSPORTO_LINE_H

#include "Stop.h"
#include <string>
#include <vector>

class Line {
    std::string code1;
    std::string code2;
    std::string name1;
    std::string name2;
    std::vector<Stop> stops;
public:
    const std::string &getCode1() const;
    const std::string &getCode2() const;
    const std::string &getName1() const;
    const std::string &getName2() const;


};


#endif //AED_TRANSPORTESPUBLICOSPORTO_LINE_H
