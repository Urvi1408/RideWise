
#include <iostream>
#include <limits>
#include <string>

#include "RideWiseSystem.h"
#include "classes/Location.h"

using namespace std;

void displayMenu() {
    cout << "\n========== RIDEWISE ==========\n";
    cout << "1. Register Passenger\n";
    cout << "2. Register Driver\n";
    cout << "3. Register Cab\n";
    cout << "4. Book a Ride\n";
    cout << "5. Display All Rides\n";
    cout << "6. View Total Rides\n";
    cout << "7. Start a Ride\n";
    cout << "8. Complete a Ride\n";
    cout << "9. Cancel a Ride\n";
    cout << "10. Book a Shared Ride\n";
    cout << "11. Exit\n";
    cout << "==============================\n";
    cout << "Enter your choice: ";
}


int main() {

    RideWiseSystem system;

    cout << "================================\n";
    cout << "       WELCOME TO RIDEWISE      \n";
    cout << "================================\n";

    cout << "\nLoading road network...\n";

    if (!system.loadRoadNetwork("data/raw/delhi_ncr_roads.gpkg")) {
        cout << "Unable to load road network!\n";
        cout << "Please check the GeoPackage file.\n";
        return 1;
    }

    cout << "\nRoad network ready!\n";

    int choice;

    do {

        displayMenu();

        if (!(cin >> choice)) {
            cout << "\nInvalid input! Please enter a number.\n";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {

            case 1: {

                int id;
                string name;

                cout << "\n--- PASSENGER REGISTRATION ---\n";

                cout << "Enter Passenger ID: ";
                cin >> id;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter Passenger Name: ";
                getline(cin, name);

                Passenger passenger(id, name);

                if (system.registerPassenger(id, passenger)) {
                    cout << "\nPassenger registered successfully!\n";
                }
                else {
                    cout << "\nPassenger ID already exists!\n";
                }

                break;
            }

            case 2: {

                int id;
                string name, phone;

                cout << "\n--- DRIVER REGISTRATION ---\n";

                cout << "Enter Driver ID: ";
                cin >> id;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter Driver Name: ";
                getline(cin, name);

                cout << "Enter Phone Number: ";
                getline(cin, phone);

                Driver driver(id, name, phone);

                if (system.registerDriver(id, driver)) {
                    cout << "\nDriver registered successfully!\n";
                }
                else {
                    cout << "\nDriver ID already exists!\n";
                }

                break;
            }

            case 3: {

                int id, capacity;
                string model, registration;

                cout << "\n--- CAB REGISTRATION ---\n";

                cout << "Enter Cab ID: ";
                cin >> id;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Enter Cab Model: ";
                getline(cin, model);

                cout << "Enter Registration Number: ";
                getline(cin, registration);

                cout << "Enter Seating Capacity: ";
                cin >> capacity;

                Cab cab(id, model, registration, capacity);

                if (system.registerCab(id, cab)) {
                    cout << "\nCab registered successfully!\n";
                }
                else {
                    cout << "\nCab ID already exists!\n";
                }

                break;
            }

            case 4: {

                int passengerID;
                int pickupID, dropID;

                cout << "\n========== BOOK A RIDE ==========\n";

                cout << "Enter Passenger ID: ";
                cin >> passengerID;

                if (!system.hasPassenger(passengerID)) {
                    cout << "\nPassenger ID not found! Please register first.\n";
                    break;
                }

                system.displayLocations();

                cout << "\nEnter Pickup Location ID: ";
                cin >> pickupID;

                cout << "Enter Destination Location ID: ";
                cin >> dropID;

                const Location* pickup =
                    system.getLocationByID(pickupID);

                const Location* drop =
                    system.getLocationByID(dropID);

                if (pickup == nullptr || drop == nullptr) {
                    cout << "\nInvalid location selection!\n";
                    break;
                }

                if (pickupID == dropID) {
                    cout << "\nPickup and destination cannot be the same!\n";
                    break;
                }

                cout << "\nPickup: " << pickup->getName();
                cout << "\nDestination: " << drop->getName() << endl;

                cout << "\nProcessing your request...\n";

                system.bookRide(
                    passengerID,
                    pickup->getLongitude(),
                    pickup->getLatitude(),
                    drop->getLongitude(),
                    drop->getLatitude()
                );

                break;
            }

            case 5: {

                cout << "\n========== ALL RIDES ==========\n";

                system.displayAllRides();

                break;
            }

            case 6: {

                cout << "\nTotal Rides Booked: "
                     << system.getTotalRides() << endl;

                break;
            }

            case 7: {

                int rideID;

                cout << "\nEnter Ride ID to start: ";
                cin >> rideID;

                system.startRide(rideID);

                break;
            }

            case 8: {

                int rideID;

                cout << "\nEnter Ride ID to complete: ";
                cin >> rideID;

                system.completeRide(rideID);

                break;
            }

            case 9: {

                int rideID;

                cout << "\nEnter Ride ID to cancel: ";
                cin >> rideID;

                system.cancelRide(rideID);

                break;
            }

            case 10: {

                int passengerAID, passengerBID;

                int pickupAID, dropAID;
                int pickupBID, dropBID;

                cout << "\n========== SHARED RIDE BOOKING ==========\n";

                cout << "\nPassenger A ID: ";
                cin >> passengerAID;

                if (!system.hasPassenger(passengerAID)) {
                    cout << "\nPassenger A not found! Please register first.\n";
                    break;
                }

                cout << "Passenger B ID: ";
                cin >> passengerBID;

                if (!system.hasPassenger(passengerBID)) {
                    cout << "\nPassenger B not found! Please register first.\n";
                    break;
                }

                if (passengerAID == passengerBID) {
                    cout << "\nPassengers must be different!\n";
                    break;
                }

                cout << "\n--- PASSENGER A ROUTE ---\n";

                system.displayLocations();

                cout << "\nPickup Location ID: ";
                cin >> pickupAID;

                cout << "Destination Location ID: ";
                cin >> dropAID;

                cout << "\n--- PASSENGER B ROUTE ---\n";

                system.displayLocations();

                cout << "\nPickup Location ID: ";
                cin >> pickupBID;

                cout << "Destination Location ID: ";
                cin >> dropBID;

                const Location* pickupA =
                    system.getLocationByID(pickupAID);

                const Location* dropA =
                    system.getLocationByID(dropAID);

                const Location* pickupB =
                    system.getLocationByID(pickupBID);

                const Location* dropB =
                    system.getLocationByID(dropBID);

                if (pickupA == nullptr || dropA == nullptr ||
                    pickupB == nullptr || dropB == nullptr) {

                    cout << "\nInvalid location selection!\n";
                    break;
                }

                if (pickupAID == dropAID ||
                    pickupBID == dropBID) {

                    cout << "\nPickup and destination cannot be the same!\n";
                    break;
                }

                cout << "\n========== SELECTED ROUTES ==========\n";

                cout << "Passenger A: "
                     << pickupA->getName()
                     << " -> "
                     << dropA->getName() << endl;

                cout << "Passenger B: "
                     << pickupB->getName()
                     << " -> "
                     << dropB->getName() << endl;


                // Book shared ride
                cout << "\nFinding a suitable shared ride...\n";

                system.bookSharedRide(
                    passengerAID,

                    pickupA->getLongitude(),
                    pickupA->getLatitude(),

                    dropA->getLongitude(),
                    dropA->getLatitude(),

                    passengerBID,

                    pickupB->getLongitude(),
                    pickupB->getLatitude(),

                    dropB->getLongitude(),
                    dropB->getLatitude()
                );

                break;
            }

            case 11: {

                cout << "\nThank you for using RideWise!\n";
                cout << "Have a safe journey!\n";

                break;
            }


            default: {

                cout << "\nInvalid choice! Please try again.\n";

            }

        }

    } while (choice != 11);

    return 0;
}
