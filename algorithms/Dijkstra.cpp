#include "Dijkstra.h"

#include <iostream>
#include <queue>
#include <limits>
#include <functional>
#include <algorithm>

using namespace std;

PathResult Dijkstra::findShortestPath(
    const Graph& graph,
    int source,
    int destination
) {

    const auto& adjList = graph.getAdjList();

    int n = static_cast<int>(adjList.size());

    if (source < 0 || destination < 0 ||
        source >= n || destination >= n) {

        return {false, 0.0, {}};
    }

    vector<double> distance(
        n, numeric_limits<double>::infinity()
    );

    vector<int> parent(n, -1);

    priority_queue<
        pair<double, int>,
        vector<pair<double, int>>,
        greater<pair<double, int>>
    > pq;

    distance[source] = 0.0;

    pq.push({0.0, source});

    while (!pq.empty()) {

        double currentDistance = pq.top().first;
        int currentNode = pq.top().second;

        pq.pop();

        if (currentDistance > distance[currentNode]) {
            continue;
        }

        if (currentNode == destination) {
            break;
        }

        for (const Edge& edge : adjList[currentNode]) {

            int neighbour = edge.destination;
            double newDistance =
                currentDistance + edge.distance;

            if (newDistance < distance[neighbour]) {

                distance[neighbour] = newDistance;

                parent[neighbour] = currentNode;

                pq.push({newDistance, neighbour});
            }
        }
    }

    if (distance[destination] ==
        numeric_limits<double>::infinity()) {

        return {false, 0.0, {}};
    }

    vector<int> path;

    int current = destination;

    while (current != -1) {

        path.push_back(current);
        current = parent[current];
    }

    reverse(path.begin(), path.end());

    return {
        true,
        distance[destination],
        path
    };
}