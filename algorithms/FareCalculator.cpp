
#include "FareCalculator.h"

#include <cmath>
#include <stdexcept>

FareBreakdown FareCalculator::calculateFare(
    double distanceMeters,
    int passengerCount,
    bool isSharedRide
) {

    if (distanceMeters < 0) {
        throw invalid_argument("Distance cannot be negative.");
    }

    if (passengerCount <= 0) {
        throw invalid_argument("Passenger count must be positive.");
    }

    if (!isSharedRide && passengerCount != 1) {
        throw invalid_argument(
            "A non-shared ride must have one passenger."
        );
    }

    FareBreakdown result;

    double distanceKm = distanceMeters / 1000.0;

    result.baseFare = BASE_FARE;

    result.distanceFare = distanceKm * PER_KM_RATE;

    result.totalBeforeDiscount =
        result.baseFare + result.distanceFare;

    if (isSharedRide) {
        result.discount =
            result.totalBeforeDiscount * SHARED_DISCOUNT;
    } else {
        result.discount = 0.0;
    }

    result.finalFare =
        result.totalBeforeDiscount - result.discount;

    result.farePerPassenger =
        result.finalFare / passengerCount;

    result.baseFare =
        round(result.baseFare * 100.0) / 100.0;

    result.distanceFare =
        round(result.distanceFare * 100.0) / 100.0;

    result.totalBeforeDiscount =
        round(result.totalBeforeDiscount * 100.0) / 100.0;

    result.discount =
        round(result.discount * 100.0) / 100.0;

    result.finalFare =
        round(result.finalFare * 100.0) / 100.0;

    result.farePerPassenger =
        round(result.farePerPassenger * 100.0) / 100.0;

    return result;
}
