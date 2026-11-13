#ifndef RIDE_H
#define RIDE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

enum class RideStatus {
    Pending,
    Ongoing,
    Completed,
    Cancelled
};

class Ride{
    private:
    int rideID;
    vector<int> passengerIDs;
    int driverID;
    int cabID;
    string pickupLocation;
    string dropLocation;
    double fare;
    RideStatus status;

    public:
    Ride(int rID,int pID,int dID,int cID,string pickup,string drop,double f);
    Ride(int rID, vector<int> pIDs, int dID, int cID,string pickup, string drop, double f);
    int getRideID();
    int getPassengerID();
    vector<int> getPassengerIDs();
    int getDriverID();
    int getCabID();
    double getFare();

    RideStatus getStatus();
    void setStatus(RideStatus s);
    void displayDetails();
};

#endif