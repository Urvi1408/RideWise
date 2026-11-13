
#ifndef RIDEWISESYSTEM_H
#define RIDEWISESYSTEM_H

#include "managers/PassengerManager.h"
#include "managers/DriverManager.h"
#include "managers/CabManager.h"
#include "managers/RideManager.h"

#include "algorithms/Graph.h"
#include "algorithms/Dijkstra.h"
#include "algorithms/FareCalculator.h"
#include "algorithms/Matching.h"

#include "classes/Location.h"

#include <string>
#include <vector>

using namespace std;

class RideWiseSystem {
private:
    PassengerManager passengerManager;
    DriverManager driverManager;
    CabManager cabManager;
    RideManager rideManager;

    Graph roadGraph;

    int nextRideID;
    int nextRequestID;

    vector<Location> locations;

    void initializeLocations();

    string getLocationName(
        double longitude,
        double latitude
    ) const;

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

    bool bookSharedRide(
        int passengerAID,
        double pickupALongitude,
        double pickupALatitude,
        double dropALongitude,
        double dropALatitude,
        int passengerBID,
        double pickupBLongitude,
        double pickupBLatitude,
        double dropBLongitude,
        double dropBLatitude
    );

    bool startRide(int rideID);
    bool completeRide(int rideID);
    bool cancelRide(int rideID);

    void displayAllRides();

    int getTotalRides() const;

    void displayLocations() const;

    const Location* getLocationByID(int locationID) const;

    bool hasPassenger(int passengerID) const;
};

#endif
