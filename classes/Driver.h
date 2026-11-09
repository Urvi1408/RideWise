#ifndef DRIVER_H
#define DRIVER_H

#include<iostream>
#include<string>

using namespace std;

class Driver{
    private:
    int driverID;
    string name;
    string phone;
    bool available;

    public:
    Driver(int id,string n,string p);
    int getID();
    string getName();
    bool isAvailable();
    void setAvailability(bool status);
    void displayDetails();

};

#endif
