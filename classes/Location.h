#ifndef LOCATION_H
#define LOCATION_H

#include <string>
using namespace std;

class Location {
private:
    int locationID;
    string name;
    double longitude;
    double latitude;

public:
    Location(int id, string n, double lon, double lat);

    int getID() const;
    string getName() const;
    double getLongitude() const;
    double getLatitude() const;
};

#endif