#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <string>
using namespace std;

class Passenger {
private:
    int passengerID;
    string name;
    string pickupLocation;
    string dropLocation;

public:
    Passenger(int id, string n, string pickup, string drop);

    int getID();
    string getName();
    string getPickup();
    string getDrop();

    void displayDetails();
};

#endif