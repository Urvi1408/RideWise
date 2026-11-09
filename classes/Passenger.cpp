#include "Passenger.h"
Passenger::Passenger(int id,string n,string pickup,string drop)
{
    passengerID=id;
    name=n;
    pickupLocation=pickup;
    dropLocation=drop;
}

int Passenger::getID()
{
    return passengerID;
}

string Passenger::getPickup()
{
    return pickupLocation;
}

string Passenger::getName()
{
    return name;
}

string Passenger::getDrop()
{
    return dropLocation;
}

void Passenger::displayDetails()
{
    cout<<"\nPassenger ID: "<<passengerID;
    cout<<"\nPassenger Name: "<<name;
    cout<<"\nPickup: "<<pickupLocation;
    cout<<"\nDestination: "<<dropLocation;
}