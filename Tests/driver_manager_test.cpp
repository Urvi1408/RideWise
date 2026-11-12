#include <iostream>
#include "../managers/DriverManager.h"

using namespace std;

int main() {
    DriverManager manager;

    Driver d1(201, "Rahul", "9876543210");
    Driver d2(202, "Aman", "9876501234");

    cout << "Adding drivers...\n";

    cout << "Driver 1: "
         << (manager.addDriver(201, d1) ? "Added" : "Failed") << endl;

    cout << "Driver 2: "
         << (manager.addDriver(202, d2) ? "Added" : "Failed") << endl;

    cout << "\nTotal drivers: " << manager.getDriverCount() << endl;

    cout << "\nSearching for driver 201...\n";

    Driver* found = manager.getDriver(201);

    if (found != nullptr) {
        found->displayDetails();
    } else {
        cout << "Driver not found!\n";
    }

    cout << "\nUpdating driver 201 availability...\n";

    if (manager.setDriverAvailability(201, false)) {
        cout << "Driver availability updated!\n";
    } else {
        cout << "Driver not found!\n";
    }

    cout << "\nDriver details after update:\n";

    found = manager.getDriver(201);

    if (found != nullptr) {
        found->displayDetails();
    }

    cout << "\nRemoving driver 202...\n";

    cout << (manager.removeDriver(202)
             ? "Driver removed!"
             : "Driver not found!") << endl;

    cout << "\nDrivers remaining: "
         << manager.getDriverCount() << endl;

    return 0;
}