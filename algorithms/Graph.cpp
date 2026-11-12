#include "Graph.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <unordered_set>

#include <gdal_priv.h>
#include <ogrsf_frmts.h>

using namespace std;

const double EARTH_RADIUS = 6371000.0;

int Graph::getOrCreateNode(double longitude, double latitude) {

    stringstream keyStream;

    keyStream << fixed << setprecision(7)
              << longitude << "," << latitude;

    string key = keyStream.str();

    auto it = nodeIndex.find(key);

    if (it != nodeIndex.end()) {
        return it->second;
    }

    int id = static_cast<int>(nodes.size());

    nodes.push_back({longitude, latitude});
    adjList.push_back({});

    nodeIndex[key] = id;

    return id;
}

double Graph::calculateDistance(
    double lat1, double lon1,
    double lat2, double lon2
) {

    const double PI = 3.14159265358979323846;

    lat1 = lat1 * PI / 180.0;
    lon1 = lon1 * PI / 180.0;

    lat2 = lat2 * PI / 180.0;
    lon2 = lon2 * PI / 180.0;

    double dLat = lat2 - lat1;
    double dLon = lon2 - lon1;

    double a =
        pow(sin(dLat / 2), 2) +
        cos(lat1) * cos(lat2) *
        pow(sin(dLon / 2), 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return EARTH_RADIUS * c;
}

bool Graph::loadFromGeoPackage(const string& filePath) {

    GDALAllRegister();

    nodes.clear();
    adjList.clear();
    nodeIndex.clear();

    GDALDataset* dataset = (GDALDataset*)GDALOpenEx(
        filePath.c_str(),
        GDAL_OF_VECTOR | GDAL_OF_READONLY,
        nullptr,
        nullptr,
        nullptr
    );

    if (dataset == nullptr) {
        cerr << "Error: Could not open GeoPackage!" << endl;
        return false;
    }

    OGRLayer* roadLayer = dataset->GetLayerByName("lines");

    if (roadLayer == nullptr) {
        cerr << "Error: Road layer not found!" << endl;
        GDALClose(dataset);
        return false;
    }

    OGRFeatureDefn* definition = roadLayer->GetLayerDefn();

    int highwayField =
        definition->GetFieldIndex("highway");

    int tagsField =
        definition->GetFieldIndex("other_tags");

    if (highwayField < 0) {
        cerr << "Error: highway field not found!" << endl;
        GDALClose(dataset);
        return false;
    }

    unordered_set<string> excludedHighways = {
        "footway",
        "steps",
        "path",
        "cycleway",
        "pedestrian",
        "bridleway",
        "corridor",
        "track",
        "construction",
        "proposed"
    };

    long long roadsProcessed = 0;
    long long segmentsProcessed = 0;

    roadLayer->ResetReading();

    OGRFeature* feature;

    while ((feature = roadLayer->GetNextFeature()) != nullptr) {

        string highway =
            feature->GetFieldAsString(highwayField);

        if (highway.empty() ||
            excludedHighways.find(highway) != excludedHighways.end()) {

            OGRFeature::DestroyFeature(feature);
            continue;
        }

        string otherTags = "";

        if (tagsField >= 0) {
            otherTags = feature->GetFieldAsString(tagsField);
        }

        bool oneWay = false;
        bool reverseOneWay = false;

        if (otherTags.find("\"oneway\"=>\"yes\"") != string::npos ||
            otherTags.find("\"oneway\"=>\"1\"") != string::npos ||
            otherTags.find("\"oneway\"=>\"true\"") != string::npos) {

            oneWay = true;
        }

        if (otherTags.find("\"oneway\"=>\"-1\"") != string::npos) {
            oneWay = true;
            reverseOneWay = true;
        }

        if (!oneWay &&
            otherTags.find("\"junction\"=>\"roundabout\"") != string::npos &&
            otherTags.find("\"oneway\"=>\"no\"") == string::npos) {

            oneWay = true;
        }

        OGRGeometry* geometry = feature->GetGeometryRef();

        if (geometry == nullptr) {
            OGRFeature::DestroyFeature(feature);
            continue;
        }

        OGRwkbGeometryType type =
            wkbFlatten(geometry->getGeometryType());

        auto processLine = [&](OGRLineString* line) {

            if (line == nullptr || line->getNumPoints() < 2) {
                return;
            }

            for (int i = 0; i < line->getNumPoints() - 1; i++) {

                OGRPoint p1;
                OGRPoint p2;

                line->getPoint(i, &p1);
                line->getPoint(i + 1, &p2);

                double lon1 = p1.getX();
                double lat1 = p1.getY();

                double lon2 = p2.getX();
                double lat2 = p2.getY();

                int u = getOrCreateNode(lon1, lat1);
                int v = getOrCreateNode(lon2, lat2);

                double distance = calculateDistance(
                    lat1, lon1, lat2, lon2
                );

                if (distance <= 0) {
                    continue;
                }

                if (reverseOneWay) {

                    adjList[v].push_back({u, distance});

                } else {

                    adjList[u].push_back({v, distance});

                    if (!oneWay) {
                        adjList[v].push_back({u, distance});
                    }
                }

                segmentsProcessed++;
            }
        };

        if (type == wkbLineString) {

            processLine((OGRLineString*)geometry);

        } else if (type == wkbMultiLineString) {

            OGRMultiLineString* multi =
                (OGRMultiLineString*)geometry;

            for (int i = 0; i < multi->getNumGeometries(); i++) {

                OGRLineString* line =
                    (OGRLineString*)multi->getGeometryRef(i);

                processLine(line);
            }
        }

        roadsProcessed++;

        OGRFeature::DestroyFeature(feature);
    }

    GDALClose(dataset);

    cout << "\nRoad network loaded successfully!" << endl;

    cout << "Road features processed: "
         << roadsProcessed << endl;

    cout << "Road segments processed: "
         << segmentsProcessed << endl;

    cout << "Graph vertices: "
         << nodes.size() << endl;

    cout << "Graph directed edges: "
         << getEdgeCount() << endl;

    return true;
}

int Graph::getEdgeCount() const {

    int count = 0;

    for (const auto& neighbours : adjList) {
        count += static_cast<int>(neighbours.size());
    }

    return count;
}

int Graph::getNodeCount() const {
    return static_cast<int>(nodes.size());
}

const vector<Node>& Graph::getNodes() const {
    return nodes;
}

const vector<vector<Edge>>& Graph::getAdjList() const {
    return adjList;
}

void Graph::displaySummary() const {

    cout << "\n========== GRAPH SUMMARY ==========" << endl;

    cout << "Vertices: " << getNodeCount() << endl;
    cout << "Directed edges: " << getEdgeCount() << endl;

    cout << "===================================" << endl;
}

int Graph::findNearestNode(double longitude, double latitude) const {

    if (nodes.empty()) {
        return -1;
    }

    int nearest = -1;
    double minDistance = 1e18;

    const double PI = 3.14159265358979323846;
    double latitudeRad = latitude * PI / 180.0;

    for (int i = 0; i < static_cast<int>(nodes.size()); i++) {

        double dx = (nodes[i].longitude - longitude)
                    * cos(latitudeRad);

        double dy = nodes[i].latitude - latitude;

        double distance = dx * dx + dy * dy;

        if (distance < minDistance) {
            minDistance = distance;
            nearest = i;
        }
    }

    return nearest;
}