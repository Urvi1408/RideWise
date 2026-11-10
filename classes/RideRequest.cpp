
#include "RideRequest.h"

RideRequest::RideRequest(int rID, int pID, string pickup, string drop, int seats, double detour) 
{
    requestID = rID;
    passengerID = pID;
    pickupLocation = pickup;
    dropLocation = drop;
    seatsRequired = seats;
    maxDetour = detour;
}

int RideRequest::getRequestID() {
    return requestID;
}

int RideRequest::getPassengerID() {
    return passengerID;
}

string RideRequest::getPickup() {
    return pickupLocation;
}

string RideRequest::getDrop() {
    return dropLocation;
}

int RideRequest::getSeatsRequired() {
    return seatsRequired;
}

double RideRequest::getMaxDetour() {
    return maxDetour;
}

void RideRequest::displayDetails() {

    cout << "\nRequest ID: " << requestID;
    cout << "\nPassenger ID: " << passengerID;

    cout << "\nPickup: " << pickupLocation;
    cout << "\nDestination: " << dropLocation;

    cout << "\nSeats Required: " << seatsRequired;
    cout << "\nMaximum Detour: " << maxDetour << " minutes";

    cout << endl;
}
