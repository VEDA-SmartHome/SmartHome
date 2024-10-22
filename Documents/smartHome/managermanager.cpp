#include "managermanager.h"

ManagerManager::ManagerManager() {
    Manager* masterManager = new Manager("veda","veda");
    masterManager->setName("관리자");

    managerList.insert(masterManager->getMid(), masterManager);
}

ManagerManager::~ManagerManager(){
    QMap<int, Manager*>::iterator it;
    for(it = managerList.begin(); it!=managerList.end(); it++){
        delete it.value();
    }
    managerList.clear();
}

QMap<int, Manager*> ManagerManager::getManagerList(){
    return managerList;
}

QList<Manager*> ManagerManager::searchByName(const QString &namePart){
    QList<Manager*> result;

    for(Manager* manager : managerList){
        if(manager->getName().contains(namePart, Qt::CaseInsensitive)){
            result.append(manager);
        }
    }
    return result;
}

