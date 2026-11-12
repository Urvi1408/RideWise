
#include <iostream>
#include "../managers/CabManager.h"

using namespace std;

int main() {
    CabManager manager;

    Cab c1(301, "Swift Dzire", "DL01AB1234", 4);
    Cab c2(302, "Innova", "DL02CD5678", 7);
    Cab c3(303, "WagonR", "DL03EF9012", 4);

    cout << "Adding cabs...\n";

    cout << "Cab 1: "
         << (manager.addCab(301, c1) ? "Added" : "Failed") << endl;

    cout << "Cab 2: "
         << (manager.addCab(302, c2) ? "Added" : "Failed") << endl;

    cout << "Cab 3: "
         << (manager.addCab(303, c3) ? "Added" : "Failed") << endl;

    cout << "\nTotal cabs: " << manager.getCabCount() << endl;

    cout << "\nSearching for cab 301...\n";

    Cab* found = manager.getCab(301);

    if (found != nullptr) {
        found->displayDetails();
    }

    cout << "\nUpdating cab 301 availability...\n";

    manager.setCabAvailability(301, false);

    found = manager.getCab(301);

    if (found != nullptr) {
        found->displayDetails();
    }

    cout << "\nFinding available cabs for 5 passengers...\n";

    vector<Cab*> suitableCabs = manager.getAvailableCabs(5);

    for (Cab* cab : suitableCabs) {
        cab->displayDetails();
    }

    cout << "\nSuitable cabs found: " << suitableCabs.size() << endl;

    cout << "\nRemoving cab 303...\n";

    cout << (manager.removeCab(303)
             ? "Cab removed!"
             : "Cab not found!") << endl;

    cout << "\nCabs remaining: " << manager.getCabCount() << endl;

    return 0;
}
