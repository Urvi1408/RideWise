
#include <iostream>

#include "classes/Passenger.h"
#include "classes/Driver.h"
#include "classes/Cab.h"
#include "classes/Ride.h"
#include "classes/RideRequest.h"

using namespace std;

int main() {

    Passenger p1(101, "Urvi", "Noida", "Delhi");

    Driver d1(201, "Rahul", "9239399393");

    Cab c1(301, "Swift Dzire", "DL8CAF1234", 4);

    Ride r1(401, 101, 201, 301,
            "Noida", "Delhi", 500);

    RideRequest req1(501, 101,
                     "Noida", "Delhi", 1, 10);

    cout << "\n===== PASSENGER =====";
    p1.displayDetails();

    cout << "\n===== DRIVER =====";
    d1.displayDetails();

    cout << "\n===== CAB =====";
    c1.displayDetails();

    cout << "\n===== RIDE =====";
    r1.displayDetails();

    r1.setStatus(RideStatus::Ongoing);

    cout << "\n===== UPDATED RIDE =====";
    r1.displayDetails();

    cout << "\n===== RIDE REQUEST =====";
    req1.displayDetails();

    return 0;
}
