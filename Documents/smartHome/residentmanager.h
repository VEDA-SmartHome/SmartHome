#ifndef RESIDENTMANAGER_H
#define RESIDENTMANAGER_H

#include <QMap>
#include <QList>
#include <QSqlDatabase>
#include "resident.h"

class ResidentManager
{
private:
    QMap<int, Resident*> residentList;
    QSqlDatabase db;
    void loadResidentsFromDB();
    void saveResidentsToDB();
public:
    ResidentManager();
    ~ResidentManager();

    Resident* addResident(int hid, QString name, QString phone,
                     QString id, QString pw, QString memo);
    void modifyResident(int rid, int hid, QString name, QString phone,
                        QString id, QString pw);
    void deleteResident(int rid);
    QMap<int, Resident*> getResidentList();
    QList<Resident*> searchByName(const QString &namePart);

    int makeRid();
};

#endif // RESIDENTMANAGER_H
