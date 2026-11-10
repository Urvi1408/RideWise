
#ifndef RIDEREQUEST_H
#define RIDEREQUEST_H

#include <iostream>
#include <string>
using namespace std;

class RideRequest {
private:
    int requestID;
    int passengerID;

    string pickupLocation;
    string dropLocation;

    int seatsRequired;
    double maxDetour;

public:
    RideRequest(int rID, int pID, string pickup,
                string drop, int seats, double detour);

    int getRequestID();
    int getPassengerID();

    string getPickup();
    string getDrop();

    int getSeatsRequired();
    double getMaxDetour();

    void displayDetails();
};

#endif
