#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Node {
    double longitude;
    double latitude;
};

struct Edge {
    int destination;
    double distance;
};

class Graph {
private:
    vector<Node> nodes;
    vector<vector<Edge>> adjList;

    unordered_map<string, int> nodeIndex;

    int getOrCreateNode(double longitude, double latitude);

    double calculateDistance(
        double lat1, double lon1,
        double lat2, double lon2
    );

public:
    bool loadFromGeoPackage(const string& filePath);

    void displaySummary() const;

    int getNodeCount() const;
    int getEdgeCount() const;

    int findNearestNode(double longitude, double latitude) const;

    double getDistanceToNearestNode(
        double longitude,
        double latitude
    ) const;

    const vector<Node>& getNodes() const;
    const vector<vector<Edge>>& getAdjList() const;
};

#endif
