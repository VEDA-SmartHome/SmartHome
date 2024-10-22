#include "login.h"
#include <QDebug>

Login::Login(ManagerManager *mManager, ResidentManager *rManager)
    : managerManager(mManager), residentManager(rManager){

}

Manager* Login::authenticateManager(const QString &id, const QString &pw){
    QMap<int, Manager*>::iterator it;
    QMap<int, Manager*> managerList = managerManager->getManagerList();
    for(it = managerList.begin(); it!=managerList.end(); it++){
        Manager* manager = it.value();
        if(manager->getId() == id && manager->getPw() == pw){
            qDebug()<<"manager login success";
            return manager;
        }
    }
    return nullptr;
}

Resident* Login::authenticateResident(const QString &id, const QString &pw){
    QMap<int, Resident*>::iterator it;
    QMap<int, Resident*> residentList = residentManager->getResidentList();
    for(it = residentList.begin(); it!=residentList.end(); it++){
        Resident* resident = it.value();
        if(resident->getId() == id && resident->getPw() == pw){
            qDebug()<<"resident login success";
            return resident;
        }
    }
    return nullptr;
}
