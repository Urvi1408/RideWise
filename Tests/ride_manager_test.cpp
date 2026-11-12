
#include <iostream>
#include "../managers/RideManager.h"

using namespace std;

int main() {

    RideManager manager;

    Ride r1(401, 101, 201, 301, "Noida", "Delhi", 250.0);
    Ride r2(402, 102, 202, 302, "Ghaziabad", "Noida", 180.0);

    cout << "Adding rides...\n";

    cout << "Ride 1: "
         << (manager.addRide(401, r1) ? "Added" : "Failed") << endl;

    cout << "Ride 2: "
         << (manager.addRide(402, r2) ? "Added" : "Failed") << endl;

    cout << "\nTotal rides: " << manager.getRideCount() << endl;

    cout << "\nSearching for ride 401...\n";

    Ride* found = manager.getRide(401);

    if (found != nullptr) {
        found->displayDetails();
    } else {
        cout << "Ride not found!\n";
    }

    cout << "\nUpdating ride 401 status to Ongoing...\n";

    cout << (manager.updateRideStatus(401, RideStatus::Ongoing)
             ? "Status updated!"
             : "Ride not found!") << endl;

    cout << "\nDisplaying all rides...\n";

    vector<Ride*> allRides = manager.getAllRides();

    for (Ride* ride : allRides) {
        ride->displayDetails();
        cout << "----------------------\n";
    }

    cout << "\nRemoving ride 402...\n";

    cout << (manager.removeRide(402)
             ? "Ride removed!"
             : "Ride not found!") << endl;

    cout << "\nRides remaining: " << manager.getRideCount() << endl;

    return 0;
}
