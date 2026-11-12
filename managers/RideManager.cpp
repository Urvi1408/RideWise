#include "RideManager.h"

bool RideManager::addRide(int rideID, const Ride& ride) {
    auto result = rides.emplace(rideID, ride);
    return result.second;
}

Ride* RideManager::getRide(int rideID) {
    auto it = rides.find(rideID);

    if (it == rides.end()) {
        return nullptr;
    }

    return &(it->second);
}

bool RideManager::removeRide(int rideID) {
    return rides.erase(rideID) > 0;
}

bool RideManager::hasRide(int rideID) const {
    return rides.find(rideID) != rides.end();
}

bool RideManager::updateRideStatus(int rideID, RideStatus status) {
    Ride* ride = getRide(rideID);

    if (ride == nullptr) {
        return false;
    }

    ride->setStatus(status);
    return true;
}

vector<Ride*> RideManager::getAllRides() {
    vector<Ride*> allRides;

    for (auto& entry : rides) {
        allRides.push_back(&(entry.second));
    }

    return allRides;
}

int RideManager::getRideCount() const {
    return static_cast<int>(rides.size());
}
