
#ifndef FARECALCULATOR_H
#define FARECALCULATOR_H

using namespace std;

struct FareBreakdown {
    double baseFare;
    double distanceFare;
    double totalBeforeDiscount;
    double discount;
    double finalFare;
    double farePerPassenger;
};

class FareCalculator {

private:
    static constexpr double BASE_FARE = 40.0;
    static constexpr double PER_KM_RATE = 12.0;
    static constexpr double SHARED_DISCOUNT = 0.20;

public:
    static FareBreakdown calculateFare(
        double distanceMeters,
        int passengerCount,
        bool isSharedRide
    );
};

#endif
