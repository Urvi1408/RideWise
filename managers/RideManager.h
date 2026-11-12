#ifndef RIDEMANAGER_H
#define RIDEMANAGER_H

#include "../classes/Ride.h"
#include <unordered_map>
#include <vector>

using namespace std;

class RideManager{
    private:
    unordered_map<int,Ride> rides;
    public:
    bool addRide(int rideID, const Ride& ride);
    Ride* getRide(int rideID);
    bool removeRide(int rideID);
    bool hasRide(int rideID)const;
    bool updateRideStatus(int rideID, RideStatus status);
    vector<Ride*> getAllRides();
    int getRideCount() const;
};

#endif