#include <iostream>
#include "algorithms/Graph.h"

using namespace std;

int main() {

    Graph roadNetwork;

    string filePath = "data/raw/delhi_ncr_roads.gpkg";

    if (!roadNetwork.loadFromGeoPackage(filePath)) {
        cout << "Failed to load road network." << endl;
        return 1;
    }

    roadNetwork.displaySummary();

    return 0;
}
