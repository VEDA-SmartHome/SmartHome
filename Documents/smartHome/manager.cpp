#include "manager.h"

Manager::Manager(QString id, QString pw)
    : Person(id, pw), mid(0){}

int Manager::getMid(){
    return mid;
}

void Manager::setMid(int id){
    this->mid = id;
}
