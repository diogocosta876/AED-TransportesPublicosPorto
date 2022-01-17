#ifndef AED_TRANSPORTESPUBLICOSPORTO_STOP_H
#define AED_TRANSPORTESPUBLICOSPORTO_STOP_H

#include <string>

class Stop {
    std::string code;
    std::string name;
    std::string zone;
    double latitude;
    double longitude;

public:
    const std::string& getCode() const;

    const std::string& getName() const;

    const std::string& getZone() const;

    double getLatitude() const;

    double getLongitude() const;
};


#endif //AED_TRANSPORTESPUBLICOSPORTO_STOP_H
