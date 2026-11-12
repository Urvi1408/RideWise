#include "Matching.h"

#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

MatchingResult Matching::findBestMatch(
    const Graph& graph,
    const MatchRequest& passengerA,
    const MatchRequest& passengerB,
    int cabCapacity
) {

    MatchingResult bestResult;

    bestResult.matched = false;
    bestResult.totalDistanceMeters = 0;
    bestResult.passengerADetourMeters = 0;
    bestResult.passengerBDetourMeters = 0;

    if (passengerA.seatsRequired <= 0 ||
        passengerB.seatsRequired <= 0 ||
        passengerA.seatsRequired + passengerB.seatsRequired > cabCapacity) {

        return bestResult;
    }

    PathResult directA = Dijkstra::findShortestPath(
        graph,
        passengerA.pickupNode,
        passengerA.dropNode
    );

    PathResult directB = Dijkstra::findShortestPath(
        graph,
        passengerB.pickupNode,
        passengerB.dropNode
    );

    if (!directA.found || !directB.found) {
        return bestResult;
    }

    // Events:
    // 0 = Passenger A pickup
    // 1 = Passenger A drop
    // 2 = Passenger B pickup
    // 3 = Passenger B drop

    int stops[4] = {
        passengerA.pickupNode,
        passengerA.dropNode,
        passengerB.pickupNode,
        passengerB.dropNode
    };

    vector<int> order = {0, 1, 2, 3};

    double shortestTotal = numeric_limits<double>::infinity();

    do {

        int positionA = -1;
        int positionADrop = -1;
        int positionB = -1;
        int positionBDrop = -1;

        for (int i = 0; i < 4; i++) {

            if (order[i] == 0) positionA = i;
            if (order[i] == 1) positionADrop = i;
            if (order[i] == 2) positionB = i;
            if (order[i] == 3) positionBDrop = i;
        }

        if (positionA > positionADrop ||
            positionB > positionBDrop) {
            continue;
        }

        vector<PathResult> legs;
        vector<double> legDistances;

        double totalDistance = 0;
        bool validRoute = true;

        for (int i = 0; i < 3; i++) {

            PathResult leg = Dijkstra::findShortestPath(
                graph,
                stops[order[i]],
                stops[order[i + 1]]
            );

            if (!leg.found) {
                validRoute = false;
                break;
            }

            legDistances.push_back(leg.totalDistance);
            totalDistance += leg.totalDistance;
            legs.push_back(leg);
        }

        if (!validRoute) {
            continue;
        }

        double distanceA = 0;
        double distanceB = 0;

        for (int i = positionA; i < positionADrop; i++) {
            distanceA += legDistances[i];
        }

        for (int i = positionB; i < positionBDrop; i++) {
            distanceB += legDistances[i];
        }

        double detourA = distanceA - directA.totalDistance;
        double detourB = distanceB - directB.totalDistance;

        detourA = max(0.0, detourA);
        detourB = max(0.0, detourB);

        if (detourA > passengerA.maxDetourMeters ||
            detourB > passengerB.maxDetourMeters) {
            continue;
        }

        if (totalDistance < shortestTotal) {

            shortestTotal = totalDistance;

            bestResult.matched = true;
            bestResult.totalDistanceMeters = totalDistance;
            bestResult.passengerADetourMeters = detourA;
            bestResult.passengerBDetourMeters = detourB;
            bestResult.stopOrder = order;

            bestResult.route.clear();

            for (const PathResult& leg : legs) {

                for (int node : leg.path) {

                    if (bestResult.route.empty() ||
                        bestResult.route.back() != node) {

                        bestResult.route.push_back(node);
                    }
                }
            }
        }

    } while (next_permutation(order.begin(), order.end()));

    return bestResult;
}
