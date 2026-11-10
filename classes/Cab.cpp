#include "Cab.h"

Cab::Cab(int id, string m,string reg,int cap)
{
    cabID=id;
    model=m;
    registrationNumber=reg;
    capacity=cap;
    available=true;
}

int Cab::getID()
{
    return cabID;
}

string Cab:: getModel()
{
    return model;
}

int Cab:: getCapacity()
{
    return capacity;
}

bool Cab:: isAvailable()
{
    return available;
}

void Cab::setAvailability(bool status)
{
    available=status;
}

void Cab::displayDetails()
{
    cout << "\nCab ID: " << cabID;
    cout << "\nModel: " << model;
    cout << "\nRegistration: " << registrationNumber;
    cout << "\nCapacity: " << capacity;
    cout << "\nAvailable: " << (available ? "Yes" : "No") << endl;
}