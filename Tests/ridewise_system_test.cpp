
#include <iostream>
#include "../RideWiseSystem.h"

using namespace std;

int main() {
    RideWiseSystem system;

    cout << "========== RIDEWISE SYSTEM TEST ==========\n";

    cout << "\nLoading road network...\n";

    if (!system.loadRoadNetwork("data/raw/delhi_ncr_roads.gpkg")) {
        cout << "Failed to load road network!\n";
        return 1;
    }

    cout << "Road network loaded successfully!\n";

    Passenger p1(101, "Aarav", "Noida", "Delhi");

    cout << "\nRegistering passenger...\n";
    cout << (system.registerPassenger(101, p1)
             ? "Passenger registered!\n"
             : "Passenger registration failed!\n");

    Driver d1(201, "Rahul", "9876543210");

    cout << "\nRegistering driver...\n";
    cout << (system.registerDriver(201, d1)
             ? "Driver registered!\n"
             : "Driver registration failed!\n");

    Cab c1(301, "Swift Dzire", "DL01AB1234", 4);

    cout << "\nRegistering cab...\n";
    cout << (system.registerCab(301, c1)
             ? "Cab registered!\n"
             : "Cab registration failed!\n");

    cout << "\nBooking ride...\n";

    bool booked = system.bookRide(
        101,
        77.2309, 28.6723,
        77.2293, 28.6793
    );

    if (!booked) {
        cout << "\nRide booking failed!\n";
        return 1;
    }

    cout << "\nTotal rides created: "
         << system.getTotalRides() << endl;

    cout << "\nDisplaying all rides...\n";
    system.displayAllRides();

    cout << "\n========== TEST COMPLETED ==========\n";

    return 0;
}
