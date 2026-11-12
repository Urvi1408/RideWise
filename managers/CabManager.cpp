#include "CabManager.h"

bool CabManager::addCab(int cabID, const Cab& cab)
{
    auto result=cabs.emplace(cabID,cab);
    return result.second;
}

Cab* CabManager:: getCab(int cabID)
{
    auto it=cabs.find(cabID);

    if(it==cabs.end())
    {
        return NULL;
    }

    return &(it->second);
}

bool CabManager::removeCab(int cabID)
{
    return cabs.erase(cabID)>0;
}

bool CabManager:: hasCab(int cabID) const{
    return cabs.find(cabID) != cabs.end();
}

bool CabManager:: setCabAvailability(int cabID,bool status)
{
    Cab* cab=getCab(cabID);
    if(cab==NULL)
    {
        return false;
    }
    cab->setAvailability(status);
    return true;
}

vector<Cab*> CabManager::getAvailableCabs(int requiredSeats) {
    vector<Cab*> availableCabs;

    for (auto& entry : cabs) {
        Cab& cab = entry.second;

        if (cab.isAvailable() && cab.getCapacity() >= requiredSeats) {
            availableCabs.push_back(&cab);
        }
    }
    return availableCabs;
}

int CabManager::getCabCount() const {
    return static_cast<int>(cabs.size());
}
