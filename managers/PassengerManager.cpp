
#include "PassengerManager.h"

bool PassengerManager::addPassenger(
    int passengerID,
    const Passenger& passenger
) {
    auto result = passengers.emplace(passengerID, passenger);

    return result.second;
}

Passenger* PassengerManager::getPassenger(int passengerID) {
    auto it = passengers.find(passengerID);

    if (it == passengers.end()) {
        return nullptr;
    }

    return &(it->second);
}

bool PassengerManager::removePassenger(int passengerID) {
    return passengers.erase(passengerID) > 0;
}

bool PassengerManager::hasPassenger(int passengerID) const {
    return passengers.find(passengerID) != passengers.end();
}

int PassengerManager::getPassengerCount() const {
    return static_cast<int>(passengers.size());
}
