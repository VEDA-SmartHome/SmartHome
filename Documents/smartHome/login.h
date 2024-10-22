#ifndef LOGIN_H
#define LOGIN_H

#include <QString>
#include "managermanager.h"
#include "residentmanager.h"

class Login
{
private:
    ManagerManager *managerManager;
    ResidentManager *residentManager;
public:
    Login(ManagerManager *mManager, ResidentManager *rManager);
    Manager* authenticateManager(const QString &id, const QString &pw);
    Resident* authenticateResident(const QString &id, const QString &pw);
};

#endif // LOGIN_H
