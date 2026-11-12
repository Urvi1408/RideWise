#include <iostream>

#include "algorithms/Graph.h"
#include "algorithms/Dijkstra.h"

using namespace std;

int main() {

    Graph roadNetwork;

    string filePath = "data/raw/delhi_ncr_roads.gpkg";

    if (!roadNetwork.loadFromGeoPackage(filePath)) {
        cout << "Could not load road network!" << endl;
        return 1;
    }

    double pickupLat = 28.6723;
    double pickupLon = 77.2309;

    double dropLat = 28.6793;
    double dropLon = 77.2293;

    int source = roadNetwork.findNearestNode(
        pickupLon, pickupLat
    );

    int destination = roadNetwork.findNearestNode(
        dropLon, dropLat
    );

    cout << "\nPickup vertex: " << source << endl;
    cout << "Drop vertex: " << destination << endl;

    cout << "\nFinding shortest route..." << endl;

    PathResult result = Dijkstra::findShortestPath(
        roadNetwork, source, destination
    );

    if (result.found) {

        cout << "\nRoute found!" << endl;

        cout << "Total distance: "
             << result.totalDistance / 1000.0
             << " km" << endl;

        cout << "Vertices in route: "
             << result.path.size() << endl;

    } else {

        cout << "\nNo route found!" << endl;
    }

    return 0;
}