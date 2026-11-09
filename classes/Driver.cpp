#include"Driver.h"

Driver::Driver(int id,string n,string p)
{
    driverID=id;
    name=n;
    phone=p;
    available=true;
}

int Driver::getID()
{
    return driverID;
}

string Driver:: getName()
{
    return name;
}

bool Driver::isAvailable()
{
    return available;
}

void Driver:: setAvailability(bool status)
{
    available=status;
}

void Driver:: displayDetails()
{cout << "\nDriver ID: " << driverID;
    cout << "\nName: " << name;
    cout << "\nPhone: " << phone;
    cout << "\nAvailable: " << (available ? "Yes" : "No") << endl;
}