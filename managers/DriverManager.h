#ifndef DRIVERMANAGER_H
#define DRIVERMANAGER_H

#include "../classes/Driver.h"
#include <unordered_map>
#include<vector>

using namespace std;

class DriverManager {
private:
    unordered_map<int, Driver> drivers;

public:
    bool addDriver(int driverID, const Driver& driver);
    Driver* getDriver(int driverID);
    bool removeDriver(int driverID);
    bool hasDriver(int driverID) const;

    bool setDriverAvailability(int driverID, bool status);

    int getDriverCount() const;
    vector<Driver*> getAvailableDrivers();
};

#endif