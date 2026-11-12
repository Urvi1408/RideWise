#include "RideWiseSystem.h"

#include <iostream>
#include <vector>

using namespace std;

RideWiseSystem::RideWiseSystem() {
    nextRideID = 1001;
}

bool RideWiseSystem::loadRoadNetwork(const string& filePath) {
    return roadGraph.loadFromGeoPackage(filePath);
}

bool RideWiseSystem::registerPassenger(
    int id, const Passenger& passenger
) {
    return passengerManager.addPassenger(id, passenger);
}

bool RideWiseSystem::registerDriver(
    int id, const Driver& driver
) {
    return driverManager.addDriver(id, driver);
}

bool RideWiseSystem::registerCab(
    int id, const Cab& cab
) {
    return cabManager.addCab(id, cab);
}

bool RideWiseSystem::bookRide(
    int passengerID,
    double pickupLongitude,
    double pickupLatitude,
    double dropLongitude,
    double dropLatitude
) {
    Passenger* passenger = passengerManager.getPassenger(passengerID);

    if (passenger == nullptr) {
        cout << "Passenger not found!\n";
        return false;
    }

    vector<Driver*> availableDrivers =
        driverManager.getAvailableDrivers();

    if (availableDrivers.empty()) {
        cout << "No available drivers!\n";
        return false;
    }

    vector<Cab*> availableCabs =
        cabManager.getAvailableCabs(1);

    if (availableCabs.empty()) {
        cout << "No suitable available cabs!\n";
        return false;
    }

    int source = roadGraph.findNearestNode(
        pickupLongitude, pickupLatitude
    );

    int destination = roadGraph.findNearestNode(
        dropLongitude, dropLatitude
    );

    if (source == -1 || destination == -1) {
        cout << "Could not locate pickup or destination on road network!\n";
        return false;
    }

    PathResult path = Dijkstra::findShortestPath(
        roadGraph, source, destination
    );

    if (!path.found) {
        cout << "No route found!\n";
        return false;
    }

    FareBreakdown fare = FareCalculator::calculateFare(
        path.totalDistance, 1, false
    );

    Driver* driver = availableDrivers[0];
    Cab* cab = availableCabs[0];

    Ride ride(
        nextRideID,
        passengerID,
        driver->getID(),
        cab->getID(),
        passenger->getPickup(),
        passenger->getDrop(),
        fare.finalFare
    );

    if (!rideManager.addRide(nextRideID, ride)) {
        cout << "Could not create ride!\n";
        return false;
    }

    driver->setAvailability(false);
    cab->setAvailability(false);

    cout << "\n========== RIDE BOOKED ==========\n";
    cout << "Ride ID: " << nextRideID << endl;
    cout << "Passenger: " << passenger->getName() << endl;
    cout << "Driver: " << driver->getName() << endl;
    cout << "Cab: " << cab->getModel() << endl;
    cout << "Distance: " << path.totalDistance / 1000.0 << " km\n";
    cout << "Fare: Rs. " << fare.finalFare << endl;
    cout << "=================================\n";

    nextRideID++;

    return true;
}

void RideWiseSystem::displayAllRides() {
    vector<Ride*> allRides = rideManager.getAllRides();

    if (allRides.empty()) {
        cout << "No rides available.\n";
        return;
    }

    for (Ride* ride : allRides) {
        ride->displayDetails();
        cout << "----------------------\n";
    }
}

int RideWiseSystem::getTotalRides() const {
    return rideManager.getRideCount();
}
