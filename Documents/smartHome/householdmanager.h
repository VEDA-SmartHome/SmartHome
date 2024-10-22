#ifndef HOUSEHOLDMANAGER_H
#define HOUSEHOLDMANAGER_H

#include <QMap>
#include <QSqlDatabase>

#include "household.h"
#include "resident.h"
#include "residentmanager.h"

class HouseholdManager
{
private:
    QMap<int, Household*> householdList;
    QMap<int, Resident*> residentList;
    QSqlDatabase db;
    void loadHouseholdsFromDB();
    void saveHouseholdsToDB();

public:
    HouseholdManager(ResidentManager &residentManager);
    ~HouseholdManager();
    void addHousehold(int hid, QString moveIn, QString car1, QString car2);
    void modifyHousehold(int hid, QString moveIn, QString car1, QString car2);
    void deleteHousehold(int hid);
    QMap<int, Household*> getHouseholdList();
    Household* searchByHid(int hid);
};

#endif // HOUSEHOLDMANAGER_H
