#include "Location.h"

Location::Location(int id, string n, double lon, double lat) {
    locationID = id;
    name = n;
    longitude = lon;
    latitude = lat;
}

int Location::getID() const {
    return locationID;
}

string Location::getName() const {
    return name;
}

double Location::getLongitude() const {
    return longitude;
}

double Location::getLatitude() const {
    return latitude;
}