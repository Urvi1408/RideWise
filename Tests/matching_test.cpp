#include <iostream>

#include "algorithms/Graph.h"
#include "algorithms/Matching.h"

using namespace std;

int main() {

    Graph roadNetwork;

    if (!roadNetwork.loadFromGeoPackage(
        "data/raw/delhi_ncr_roads.gpkg"
    )) {
        cout << "Could not load road network!" << endl;
        return 1;
    }

    double pickupALon = 77.2309;
    double pickupALat = 28.6723;

    double dropALon = 77.2293;
    double dropALat = 28.6793;

    double pickupBLon = 77.2320;
    double pickupBLat = 28.6730;

    double dropBLon = 77.2310;
    double dropBLat = 28.6780;

    MatchRequest passengerA;

    passengerA.requestID = 1;
    passengerA.pickupNode =
        roadNetwork.findNearestNode(pickupALon, pickupALat);
    passengerA.dropNode =
        roadNetwork.findNearestNode(dropALon, dropALat);
    passengerA.seatsRequired = 1;
    passengerA.maxDetourMeters = 1000;

    MatchRequest passengerB;

    passengerB.requestID = 2;
    passengerB.pickupNode =
        roadNetwork.findNearestNode(pickupBLon, pickupBLat);
    passengerB.dropNode =
        roadNetwork.findNearestNode(dropBLon, dropBLat);
    passengerB.seatsRequired = 1;
    passengerB.maxDetourMeters = 1000;

    int cabCapacity = 4;

    cout << "\nChecking passenger compatibility..." << endl;

    MatchingResult result = Matching::findBestMatch(
        roadNetwork,
        passengerA,
        passengerB,
        cabCapacity
    );

    if (result.matched) {

        cout << "\nSHARED RIDE MATCH FOUND!" << endl;

        cout << "\nTotal shared distance: "
             << result.totalDistanceMeters / 1000.0
             << " km" << endl;

        cout << "Passenger A detour: "
             << result.passengerADetourMeters
             << " metres" << endl;

        cout << "Passenger B detour: "
             << result.passengerBDetourMeters
             << " metres" << endl;

        cout << "\nStop order: ";

        for (int stop : result.stopOrder) {

            if (stop == 0) cout << "A Pickup -> ";
            if (stop == 1) cout << "A Drop -> ";
            if (stop == 2) cout << "B Pickup -> ";
            if (stop == 3) cout << "B Drop -> ";
        }

        cout << "END" << endl;

        cout << "\nTotal vertices in shared route: "
             << result.route.size() << endl;

    } else {

        cout << "\nNo compatible shared ride found!" << endl;
    }

    return 0;
}
