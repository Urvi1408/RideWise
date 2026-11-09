#include<iostream>
#include "classes/Passenger.h"
#include "classes/Driver.h"
using namespace std;

int main()
{
    Passenger p1(101,"Urvi","Noida","Delhi");
    p1.displayDetails();

    Driver d1(201,"Rahul","9239399393");
    d1.displayDetails();
    d1.setAvailability(false);

    cout<<"After Assigning ride: ";
    d1.displayDetails();
    return 0;
}