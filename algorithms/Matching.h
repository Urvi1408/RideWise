
#ifndef MATCHING_H
#define MATCHING_H

#include "Graph.h"
#include "Dijkstra.h"
#include <vector>

using namespace std;

struct MatchRequest {
    int requestID;
    int pickupNode;
    int dropNode;
    int seatsRequired;
    double maxDetourMeters;
};

struct MatchingResult {
    bool matched;
    double totalDistanceMeters;
    double passengerADetourMeters;
    double passengerBDetourMeters;
    vector<int> route;
    vector<int> stopOrder;
};

class Matching {
public:
    static MatchingResult findBestMatch(
        const Graph& graph,
        const MatchRequest& passengerA,
        const MatchRequest& passengerB,
        int cabCapacity
    );
};

#endif
