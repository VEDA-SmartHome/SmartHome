#ifndef MANAGERMANAGER_H
#define MANAGERMANAGER_H

#include <QMap>
#include "manager.h"

class ManagerManager
{
private:
    QMap<int, Manager*> managerList;

public:
    ManagerManager();
    ~ManagerManager();
    QMap<int, Manager*> getManagerList();
    QList<Manager*> searchByName(const QString &namePart);
};

#endif // MANAGERMANAGER_H
