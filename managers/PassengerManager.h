
#ifndef PASSENGERMANAGER_H
#define PASSENGERMANAGER_H

#include "../classes/Passenger.h"
#include <unordered_map>

using namespace std;

class PassengerManager {
private:
    unordered_map<int, Passenger> passengers;

public:
    bool addPassenger(int passengerID, const Passenger& passenger);
    Passenger* getPassenger(int passengerID);
    bool removePassenger(int passengerID);
    bool hasPassenger(int passengerID) const;
    int getPassengerCount() const;
};

#endif
