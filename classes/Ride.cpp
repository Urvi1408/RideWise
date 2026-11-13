#include "Ride.h"

Ride:: Ride(int rID,int pID,int dID,int cID,string pickup,string drop,double f)
{
    rideID=rID;
    passengerIDs.push_back(pID);
    driverID=dID;
    cabID=cID;
    pickupLocation=pickup;
    dropLocation=drop;
    fare=f;
    status = RideStatus::Pending;
}

Ride::Ride(int rID, vector<int> pIDs, int dID, int cID,
           string pickup, string drop, double f)
{
    rideID = rID;
    passengerIDs = pIDs;
    driverID = dID;
    cabID = cID;
    pickupLocation = pickup;
    dropLocation = drop;
    fare = f;
    status = RideStatus::Pending;
}

int Ride:: getRideID()
{
    return rideID;
}

int Ride::getPassengerID() {
    return passengerIDs.empty() ? -1 : passengerIDs[0];
}

vector<int> Ride::getPassengerIDs() {
    return passengerIDs;
}

int Ride::getDriverID() {
    return driverID;
}

int Ride::getCabID() {
    return cabID;
}

double Ride::getFare() {
    return fare;
}

RideStatus Ride::getStatus() {
    return status;
}

void Ride::setStatus(RideStatus s) {
    status = s;
}
void Ride::displayDetails() {

    cout << "\nRide ID: " << rideID;
    cout << "\nPassenger IDs: ";

    for (int id : passengerIDs) {
        cout << id << " ";
    }
    cout << "\nDriver ID: " << driverID;
    cout << "\nCab ID: " << cabID;
    cout << "\nPickup: " << pickupLocation;
    cout << "\nDestination: " << dropLocation;

    cout << "\nFare: Rs. " << fare;

    cout << "\nStatus: ";

    switch(status) {
        case RideStatus::Pending:
            cout << "Pending";
            break;

        case RideStatus::Ongoing:
            cout << "Ongoing";
            break;

        case RideStatus::Completed:
            cout << "Completed";
            break;

        case RideStatus::Cancelled:
            cout << "Cancelled";
            break;
    }
    cout << endl;
}