
#include <iostream>
#include <iomanip>

#include "algorithms/FareCalculator.h"

using namespace std;

int main() {

    // Distance from previous matching test
    double distanceMeters = 7478.05;

    int passengerCount = 2;

    bool isSharedRide = true;

    FareBreakdown fare =
        FareCalculator::calculateFare(
            distanceMeters,
            passengerCount,
            isSharedRide
        );

    cout << fixed << setprecision(2);

    cout << "\n========== RIDEWISE FARE DETAILS ==========\n";

    cout << "Distance: "
         << distanceMeters / 1000.0
         << " km\n";

    cout << "Base fare: Rs. "
         << fare.baseFare << endl;

    cout << "Distance fare: Rs. "
         << fare.distanceFare << endl;

    cout << "Total before discount: Rs. "
         << fare.totalBeforeDiscount << endl;

    cout << "Shared ride discount: Rs. "
         << fare.discount << endl;

    cout << "Final ride fare: Rs. "
         << fare.finalFare << endl;

    cout << "Number of passengers: "
         << passengerCount << endl;

    cout << "Fare per passenger: Rs. "
         << fare.farePerPassenger << endl;

    cout << "===========================================\n";

    return 0;
}