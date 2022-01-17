#include "Stop.h"
using namespace std;

Stop::Stop(const string& code, const string& name, const string& zone, double latitude, double longitude) {
    this->code = code;
    this->name = name;
    this->zone = zone;
    this->latitude = latitude;
    this->longitude = longitude;
}

const string& Stop::getCode() const {
    return code;
}

const string& Stop::getName() const {
    return name;
}

const string& Stop::getZone() const {
    return zone;
}

double Stop::getLatitude() const {
    return latitude;
}

double Stop::getLongitude() const {
    return longitude;
}



