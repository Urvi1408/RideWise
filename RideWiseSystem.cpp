#include "RideWiseSystem.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

RideWiseSystem::RideWiseSystem() {
    nextRideID = 1001;
    nextRequestID = 1;

    initializeLocations();
}

void RideWiseSystem::initializeLocations() {

    locations.push_back(Location(1, "JIIT Sector 128", 77.3660, 28.5206));
    locations.push_back(Location(2, "Noida Sector 62", 77.3640, 28.6270));
    locations.push_back(Location(3, "Noida Sector 18", 77.3260, 28.5708));
    locations.push_back(Location(4, "Botanical Garden Metro", 77.3340, 28.5647));
    locations.push_back(Location(5, "Noida City Centre", 77.3560, 28.5744));
    locations.push_back(Location(6, "Noida Electronic City", 77.3720, 28.6270));
    locations.push_back(Location(7, "DLF Mall of India", 77.3210, 28.5670));
    locations.push_back(Location(8, "Okhla Bird Sanctuary", 77.3090, 28.5520));
    locations.push_back(Location(9, "Noida Sector 137", 77.4090, 28.5040));
    locations.push_back(Location(10, "Pari Chowk", 77.5080, 28.4650));
    locations.push_back(Location(11, "Knowledge Park", 77.5010, 28.4500));
    locations.push_back(Location(12, "India Gate", 77.2295, 28.6129));
    locations.push_back(Location(13, "Connaught Place", 77.2167, 28.6315));
    locations.push_back(Location(14, "New Delhi Railway Station", 77.2190, 28.6430));
    locations.push_back(Location(15, "Akshardham Temple", 77.2773, 28.6127));
    locations.push_back(Location(16, "Mayur Vihar Phase 1", 77.2940, 28.6040));
    locations.push_back(Location(17, "Anand Vihar ISBT", 77.3160, 28.6460));
    locations.push_back(Location(18, "Indira Gandhi Airport", 77.1000, 28.5562));
    locations.push_back(Location(19, "Lajpat Nagar", 77.2430, 28.5677));
    locations.push_back(Location(20, "Noida Sector 50", 77.3670, 28.5700));
}

void RideWiseSystem::displayLocations() const {

    cout << "\n========== AVAILABLE LOCATIONS ==========\n";

    for (const Location& location : locations) {
        cout << location.getID() << ". "
             << location.getName() << endl;
    }

    cout << "=========================================\n";
}

const Location* RideWiseSystem::getLocationByID(int locationID) const {

    for (const Location& location : locations) {

        if (location.getID() == locationID) {
            return &location;
        }
    }

    return nullptr;
}

string RideWiseSystem::getLocationName(
    double longitude,
    double latitude
) const {

    double minimumDifference = numeric_limits<double>::max();
    string selectedName = "Unknown Location";

    for (const Location& location : locations) {

        double lonDifference = location.getLongitude() - longitude;
        double latDifference = location.getLatitude() - latitude;

        double difference =
            lonDifference * lonDifference +
            latDifference * latDifference;

        if (difference < minimumDifference) {
            minimumDifference = difference;
            selectedName = location.getName();
        }
    }

    return selectedName;
}

bool RideWiseSystem::loadRoadNetwork(const string& filePath) {
    return roadGraph.loadFromGeoPackage(filePath);
}

bool RideWiseSystem::registerPassenger(
    int id,
    const Passenger& passenger
) {
    return passengerManager.addPassenger(id, passenger);
}

bool RideWiseSystem::registerDriver(
    int id,
    const Driver& driver
) {
    return driverManager.addDriver(id, driver);
}

bool RideWiseSystem::registerCab(
    int id,
    const Cab& cab
) {
    return cabManager.addCab(id, cab);
}

bool RideWiseSystem::hasPassenger(int passengerID) const {
    return passengerManager.hasPassenger(passengerID);
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
        cout << "Could not locate pickup or destination!\n";
        return false;
    }

    cout << "\n========== ROUTE DIAGNOSTICS ==========\n";

    cout << "Pickup nearest graph node ID: "
         << source << endl;

    cout << "Pickup distance to nearest road node: "
         << roadGraph.getDistanceToNearestNode(
                pickupLongitude, pickupLatitude
            ) << " metres\n";

    cout << "Destination nearest graph node ID: "
         << destination << endl;

    cout << "Destination distance to nearest road node: "
         << roadGraph.getDistanceToNearestNode(
                dropLongitude, dropLatitude
            ) << " metres\n";

    cout << "=======================================\n";

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

    string pickupName = getLocationName(
        pickupLongitude, pickupLatitude
    );

    string dropName = getLocationName(
        dropLongitude, dropLatitude
    );

    Ride ride(
        nextRideID,
        passengerID,
        driver->getID(),
        cab->getID(),
        pickupName,
        dropName,
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
    cout << "Pickup: " << pickupName << endl;
    cout << "Destination: " << dropName << endl;
    cout << "Driver: " << driver->getName() << endl;
    cout << "Cab: " << cab->getModel() << endl;
    cout << "Distance: " << path.totalDistance / 1000.0 << " km\n";
    cout << "Fare: Rs. " << fare.finalFare << endl;
    cout << "=================================\n";

    nextRideID++;

    return true;
}

bool RideWiseSystem::bookSharedRide(
    int passengerAID,
    double pickupALongitude,
    double pickupALatitude,
    double dropALongitude,
    double dropALatitude,
    int passengerBID,
    double pickupBLongitude,
    double pickupBLatitude,
    double dropBLongitude,
    double dropBLatitude
) {

    Passenger* passengerA = passengerManager.getPassenger(passengerAID);
    Passenger* passengerB = passengerManager.getPassenger(passengerBID);

    if (passengerA == nullptr || passengerB == nullptr) {
        cout << "One or both passengers not found!\n";
        return false;
    }

    if (passengerAID == passengerBID) {
        cout << "Passengers must be different!\n";
        return false;
    }

    vector<Driver*> availableDrivers =
        driverManager.getAvailableDrivers();

    if (availableDrivers.empty()) {
        cout << "No available drivers!\n";
        return false;
    }

    vector<Cab*> availableCabs =
        cabManager.getAvailableCabs(2);

    if (availableCabs.empty()) {
        cout << "No suitable cabs available!\n";
        return false;
    }

    int pickupA = roadGraph.findNearestNode(
        pickupALongitude, pickupALatitude
    );

    int dropA = roadGraph.findNearestNode(
        dropALongitude, dropALatitude
    );

    int pickupB = roadGraph.findNearestNode(
        pickupBLongitude, pickupBLatitude
    );

    int dropB = roadGraph.findNearestNode(
        dropBLongitude, dropBLatitude
    );

    if (pickupA == -1 || dropA == -1 ||
        pickupB == -1 || dropB == -1) {

        cout << "Could not locate passenger locations!\n";
        return false;
    }

    MatchRequest requestA = {
        nextRequestID++, pickupA, dropA, 1, 2000
    };

    MatchRequest requestB = {
        nextRequestID++, pickupB, dropB, 1, 2000
    };

    MatchingResult match;
    Cab* selectedCab = nullptr;

    for (Cab* cab : availableCabs) {

        match = Matching::findBestMatch(
            roadGraph,
            requestA,
            requestB,
            cab->getCapacity()
        );

        if (match.matched) {
            selectedCab = cab;
            break;
        }
    }

    if (selectedCab == nullptr) {
        cout << "No suitable shared route found!\n";
        return false;
    }

    FareBreakdown fare = FareCalculator::calculateFare(
        match.totalDistanceMeters, 2, true
    );

    vector<int> passengerIDs = {
        passengerAID,
        passengerBID
    };

    string pickupDetails =
        getLocationName(pickupALongitude, pickupALatitude)
        + " / " +
        getLocationName(pickupBLongitude, pickupBLatitude);

    string dropDetails =
        getLocationName(dropALongitude, dropALatitude)
        + " / " +
        getLocationName(dropBLongitude, dropBLatitude);

    Ride ride(
        nextRideID,
        passengerIDs,
        availableDrivers[0]->getID(),
        selectedCab->getID(),
        pickupDetails,
        dropDetails,
        fare.finalFare
    );

    if (!rideManager.addRide(nextRideID, ride)) {
        cout << "Could not create shared ride!\n";
        return false;
    }

    availableDrivers[0]->setAvailability(false);
    selectedCab->setAvailability(false);

    cout << "\n======= SHARED RIDE BOOKED =======\n";

    cout << "Ride ID: " << nextRideID << endl;
    cout << "Passenger A: " << passengerA->getName() << endl;
    cout << "Passenger B: " << passengerB->getName() << endl;

    cout << "Passenger A Route: "
         << getLocationName(pickupALongitude, pickupALatitude)
         << " -> "
         << getLocationName(dropALongitude, dropALatitude)
         << endl;

    cout << "Passenger B Route: "
         << getLocationName(pickupBLongitude, pickupBLatitude)
         << " -> "
         << getLocationName(dropBLongitude, dropBLatitude)
         << endl;

    cout << "Driver: " << availableDrivers[0]->getName() << endl;
    cout << "Cab: " << selectedCab->getModel() << endl;

    cout << "Total Distance: "
         << match.totalDistanceMeters / 1000.0 << " km\n";

    cout << "Total Shared Fare: Rs. "
         << fare.finalFare << endl;

    cout << "Fare Per Passenger: Rs. "
         << fare.farePerPassenger << endl;

    cout << "Passenger A Detour: "
         << match.passengerADetourMeters << " metres\n";

    cout << "Passenger B Detour: "
         << match.passengerBDetourMeters << " metres\n";

    cout << "==================================\n";

    nextRideID++;

    return true;
}

bool RideWiseSystem::startRide(int rideID) {

    Ride* ride = rideManager.getRide(rideID);

    if (ride == nullptr) {
        cout << "Ride not found!\n";
        return false;
    }

    if (ride->getStatus() != RideStatus::Pending) {
        cout << "Only pending rides can be started!\n";
        return false;
    }

    ride->setStatus(RideStatus::Ongoing);

    cout << "Ride started successfully!\n";

    return true;
}

bool RideWiseSystem::completeRide(int rideID) {

    Ride* ride = rideManager.getRide(rideID);

    if (ride == nullptr) {
        cout << "Ride not found!\n";
        return false;
    }

    if (ride->getStatus() != RideStatus::Ongoing) {
        cout << "Only ongoing rides can be completed!\n";
        return false;
    }

    int driverID = ride->getDriverID();
    int cabID = ride->getCabID();

    ride->setStatus(RideStatus::Completed);

    driverManager.setDriverAvailability(driverID, true);
    cabManager.setCabAvailability(cabID, true);

    cout << "Ride completed successfully!\n";
    cout << "Driver and cab are now available.\n";

    return true;
}

bool RideWiseSystem::cancelRide(int rideID) {

    Ride* ride = rideManager.getRide(rideID);

    if (ride == nullptr) {
        cout << "Ride not found!\n";
        return false;
    }

    RideStatus currentStatus = ride->getStatus();

    if (currentStatus != RideStatus::Pending &&
        currentStatus != RideStatus::Ongoing) {

        cout << "This ride cannot be cancelled!\n";
        return false;
    }

    int driverID = ride->getDriverID();
    int cabID = ride->getCabID();

    ride->setStatus(RideStatus::Cancelled);

    driverManager.setDriverAvailability(driverID, true);
    cabManager.setCabAvailability(cabID, true);

    cout << "Ride cancelled successfully!\n";
    cout << "Driver and cab are now available.\n";

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
