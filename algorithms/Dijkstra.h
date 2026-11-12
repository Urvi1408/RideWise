#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"
#include <vector>

using namespace std;

struct PathResult {
    bool found;
    double totalDistance;
    vector<int> path;
};

class Dijkstra {
public:
    static PathResult findShortestPath(
        const Graph& graph,
        int source,
        int destination
    );
};

#endif