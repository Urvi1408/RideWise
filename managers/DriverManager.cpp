#include "DriverManager.h"

bool DriverManager::addDriver(int driverID, const Driver& driver) {
    auto result = drivers.emplace(driverID, driver);
    return result.second;
}

Driver* DriverManager::getDriver(int driverID) {
    auto it = drivers.find(driverID);

    if (it == drivers.end()) {
        return nullptr;
    }

    return &(it->second);
}

bool DriverManager::removeDriver(int driverID) {
    return drivers.erase(driverID) > 0;
}

bool DriverManager::hasDriver(int driverID) const {
    return drivers.find(driverID) != drivers.end();
}

bool DriverManager::setDriverAvailability(int driverID, bool status) {
    Driver* driver = getDriver(driverID);

    if (driver == nullptr) {
        return false;
    }

    driver->setAvailability(status);
    return true;
}

int DriverManager::getDriverCount() const {
    return static_cast<int>(drivers.size());
}

vector<Driver*> DriverManager::getAvailableDrivers() {
    vector<Driver*> availableDrivers;

    for (auto& entry : drivers) {
        Driver& driver = entry.second;

        if (driver.isAvailable()) {
            availableDrivers.push_back(&driver);
        }
    }

    return availableDrivers;
}