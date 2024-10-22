#include "household.h"
#include <QDebug>

Household::Household(int hid, int person, QString moveIn, QString car1, QString car2) :
    hid(hid), person(person), moveIn(moveIn), car1(car1), car2(car2), familyList(QList<Resident*>()){
    lightState = false;
    curtainState = false;
    gasState = false;
}

void Household::addFamilyMember(Resident *resident){
    familyList.append(resident);
    setPerson(++(this->person));
}

void Household::deleteFamilyMember(Resident *resident){
    if (familyList.removeOne(resident)) {
        qDebug() << "Resident removed from the list.";
    } else {
        qDebug() << "Resident not found in the list.";
    }
}

int Household::getHid(){
    return hid;
}

void Household::setHid(int hid){
    this->hid = hid;
}

int Household::getPerson(){
    return person;
}

void Household::setPerson(int person){
    this->person = person;
}

QString Household::getMoveIn(){
    return moveIn;
}

void Household::setMoveIn(const QString &moveIn){
    this->moveIn = moveIn;
}

QString Household::getCar1(){
    return car1;
}

void Household::setCar1(const QString &car1){
    this->car1 = car1;
}

QString Household::getCar2(){
    return car2;
}

void Household::setCar2(const QString &car2){
    this->car2 = car2;
}

QList<Resident*> Household::getFamilyList(){
    return familyList;
}

bool Household::getLightState(){
    return lightState;
}

void Household::setLightState(bool state){
    this->lightState = state;
}

bool Household::getGasState(){
    return gasState;
}

void Household::setGasState(bool state){
    this->gasState = state;
}

bool Household::getCurtainState(){
    return curtainState;
}

void Household::setCurtainState(bool state){
    this->curtainState = state;
}
