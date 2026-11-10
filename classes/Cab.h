#ifndef CAB_H
#define CAB_H

#include<iostream>
#include<string>
using namespace std;

class Cab
{
    private:
    int cabID;
    string model;
    string registrationNumber;
    int capacity;
    bool available;

    public:
    Cab(int id,string m,string reg,int cap);
    int getID();
    string getModel();
    int getCapacity();
    bool isAvailable();
    void setAvailability(bool status);
    void displayDetails();
};

#endif