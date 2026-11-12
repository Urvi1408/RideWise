
#include <iostream>
#include <gdal_priv.h>
#include <ogrsf_frmts.h>

using namespace std;

int main() {

    // Register GDAL drivers
    GDALAllRegister();

    // Path to the GeoPackage
    const char* filePath = "data/raw/delhi_ncr_roads.gpkg";

    // Open dataset in read-only mode
    GDALDataset* dataset = (GDALDataset*)GDALOpenEx(
        filePath,
        GDAL_OF_VECTOR | GDAL_OF_READONLY,
        nullptr,
        nullptr,
        nullptr
    );

    if (dataset == nullptr) {
        cout << "Error: Could not open GeoPackage!" << endl;
        return 1;
    }

    cout << "GeoPackage opened successfully!" << endl;

    // Display available layers
    int layerCount = dataset->GetLayerCount();

    cout << "\nNumber of layers: " << layerCount << endl;

    for (int i = 0; i < layerCount; i++) {

        OGRLayer* layer = dataset->GetLayer(i);

        cout << "\nLayer " << i + 1 << ": "
             << layer->GetName() << endl;

        cout << "Number of features: "
             << layer->GetFeatureCount() << endl;
    }

    // Access road layer
    OGRLayer* roadLayer = dataset->GetLayerByName("lines");

    if (roadLayer == nullptr) {
        cout << "\nRoad layer not found!" << endl;
        GDALClose(dataset);
        return 1;
    }

    cout << "\n========== ROAD DATA ==========" << endl;

    OGRFeatureDefn* definition = roadLayer->GetLayerDefn();

    int fieldCount = definition->GetFieldCount();

    // Display available fields
    cout << "\nAvailable fields:" << endl;

    for (int i = 0; i < fieldCount; i++) {

        OGRFieldDefn* field = definition->GetFieldDefn(i);

        cout << field->GetNameRef() << endl;
    }

    // Read first five road records
    cout << "\nFirst five road records:\n" << endl;

    roadLayer->ResetReading();

    OGRFeature* feature;
    int count = 0;

    while ((feature = roadLayer->GetNextFeature()) != nullptr
           && count < 5) {

        cout << "\nRoad " << count + 1 << endl;

        // Display road attributes
        for (int i = 0; i < fieldCount; i++) {

            OGRFieldDefn* field = definition->GetFieldDefn(i);

            cout << field->GetNameRef() << ": "
                 << feature->GetFieldAsString(i) << endl;
        }

        // Read road geometry
        OGRGeometry* geometry = feature->GetGeometryRef();

        if (geometry != nullptr && count == 0) {

            cout << "\nGeometry type: "
                 << geometry->getGeometryName() << endl;

            OGRwkbGeometryType type =
                wkbFlatten(geometry->getGeometryType());

            OGRLineString* line = nullptr;

            if (type == wkbLineString) {

                line = (OGRLineString*)geometry;
            }
            else if (type == wkbMultiLineString) {

                OGRMultiLineString* multi =
                    (OGRMultiLineString*)geometry;

                if (multi->getNumGeometries() > 0) {

                    line = (OGRLineString*)multi->getGeometryRef(0);
                }
            }

            if (line != nullptr && line->getNumPoints() > 0) {

                cout << "Number of coordinates: "
                     << line->getNumPoints() << endl;

                // Starting coordinate
                OGRPoint startPoint;
                line->getPoint(0, &startPoint);

                cout << "Starting coordinate: "
                     << startPoint.getX() << ", "
                     << startPoint.getY() << endl;

                // Ending coordinate
                int last = line->getNumPoints() - 1;

                OGRPoint endPoint;
                line->getPoint(last, &endPoint);

                cout << "Ending coordinate: "
                     << endPoint.getX() << ", "
                     << endPoint.getY() << endl;
            }
        }

        cout << "------------------------" << endl;

        OGRFeature::DestroyFeature(feature);
        count++;
    }

    // Close dataset
    GDALClose(dataset);

    cout << "\nDataset reading completed!" << endl;

    return 0;
}
