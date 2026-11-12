#include <iostream>
#include "algorithms/Graph.h"

using namespace std;

int main() {

    Graph city;

    city.addRoad("Noida", "Delhi", 15);
    city.addRoad("Noida", "Ghaziabad", 12);
    city.addRoad("Delhi", "Faridabad", 20);
    city.addRoad("Ghaziabad", "Delhi", 18);
    city.addRoad("Noida", "Greater Noida", 10);
    city.addRoad("Greater Noida", "Delhi", 25);

    cout << "===== RIDEWISE CITY GRAPH =====\n";

    city.displayGraph();

    return 0;
}
