
#ifndef RIDEWISESYSTEM_H
#define RIDEWISESYSTEM_H

#include "managers/PassengerManager.h"
#include "managers/DriverManager.h"
#include "managers/CabManager.h"
#include "managers/RideManager.h"

#include "algorithms/Graph.h"
#include "algorithms/Dijkstra.h"
#include "algorithms/FareCalculator.h"

#include <string>

using namespace std;

class RideWiseSystem {
private:
    PassengerManager passengerManager;
    DriverManager driverManager;
    CabManager cabManager;
    RideManager rideManager;

    Graph roadGraph;

    int nextRideID;

public:
    RideWiseSystem();

    bool loadRoadNetwork(const string& filePath);

    bool registerPassenger(int id, const Passenger& passenger);
    bool registerDriver(int id, const Driver& driver);
    bool registerCab(int id, const Cab& cab);

    bool bookRide(
        int passengerID,
        double pickupLongitude,
        double pickupLatitude,
        double dropLongitude,
        double dropLatitude
    );

    void displayAllRides();

    int getTotalRides() const;
};

#endif
