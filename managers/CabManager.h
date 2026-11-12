#ifndef CABMANAGER_H
#define CABMANAGER_H

#include "../classes/Cab.h"
#include<unordered_map>
#include<vector>

using namespace std;

class CabManager {
    private:
    unordered_map<int, Cab> cabs;

    public:
        bool addCab(int CabID, const Cab& cab);
        Cab* getCab(int cabID);
        bool removeCab(int cabID);
        bool hasCab(int cabID) const;
        bool setCabAvailability(int CabID, bool status);

        vector<Cab*> getAvailableCabs(int requiredSeats);
        int getCabCount() const;
};

#endif