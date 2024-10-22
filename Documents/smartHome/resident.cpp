#include "resident.h"

Resident::Resident(int rid, int hid, QString name, QString phone, QString id, QString pw, QString memo)
    :  Person(id, pw, name), rid(rid), hid(hid), phone(phone), memo(memo) {}

int Resident::getRid(){
    return rid;
}

void Resident::setRid(int rid){
    this->rid = rid;
}

int Resident::getHid(){
    return hid;
}

void Resident::setHid(int hid){
    this->hid = hid;
}

QString Resident::getPhone(){
    return phone;
}

void Resident::setPhone(const QString &phone){
    this->phone = phone;
}

QString Resident::getMemo(){
    return memo;
}

void Resident::setMemo(const QString &memo){
    this->memo = memo;
}

