#include "Passenger.h"

Passenger::Passenger(int id, string n) {
    passengerID = id;
    name = n;
}

int Passenger::getID() const {
    return passengerID;
}

string Passenger::getName() const {
    return name;
}

void Passenger::displayDetails() const {
    cout << "\nPassenger ID: " << passengerID;
    cout << "\nPassenger Name: " << name;
}
