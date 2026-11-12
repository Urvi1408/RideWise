
#include <iostream>
#include "../managers/PassengerManager.h"

using namespace std;

int main() {

    PassengerManager manager;

    Passenger p1(101, "Aarav", "Noida", "Delhi");
    Passenger p2(102, "Riya", "Ghaziabad", "Noida");

    cout << "Adding passengers...\n";

    cout << "Passenger 1: "
         << (manager.addPassenger(101, p1) ? "Added" : "Failed")
         << endl;

    cout << "Passenger 2: "
         << (manager.addPassenger(102, p2) ? "Added" : "Failed")
         << endl;

    cout << "\nTotal passengers: "
         << manager.getPassengerCount() << endl;

    cout << "\nSearching for passenger 101...\n";

    Passenger* found = manager.getPassenger(101);

    if (found != nullptr) {
        found->displayDetails();
    } else {
        cout << "Passenger not found!\n";
    }

    cout << "\nRemoving passenger 102...\n";

    cout << (manager.removePassenger(102)
             ? "Passenger removed!"
             : "Passenger not found!")
         << endl;

    cout << "\nPassengers remaining: "
         << manager.getPassengerCount() << endl;

    return 0;
}
