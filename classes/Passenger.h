#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <string>
using namespace std;

class Passenger {
private:
    int passengerID;
    string name;

public:
    Passenger(int id, string n);

    int getID() const;
    string getName() const;

    void displayDetails() const;
};

#endif