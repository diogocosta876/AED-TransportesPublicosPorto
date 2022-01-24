#ifndef AED_TRANSPORTESPUBLICOSPORTO_STOP_H
#define AED_TRANSPORTESPUBLICOSPORTO_STOP_H

#include <string>

using namespace std;

class Stop {
    string code;
    string name;
    string zone;
    double latitude;
    double longitude;

public:
    /**
     * Construtor da classe
     * @param code código único da paragem
     * @param name nome da paragem
     * @param zone zona da paragem
     * @param latitude
     * @param longitude
     */
    Stop(const string &code, const string &name, const string &zone, double latitude, double longitude);
    /** Getter do atributo code */
    const std::string& getCode() const;
    /** Getter do atributo name */
    const std::string& getName() const;
    /** Getter do atributo zone */
    const std::string& getZone() const;
    /** Getter do atributo latitude */
    double getLatitude() const;
    /** Getter do atributo longitude */
    double getLongitude() const;
};


#endif //AED_TRANSPORTESPUBLICOSPORTO_STOP_H
