#ifndef HOUSEHOLD_H
#define HOUSEHOLD_H

#include <QString>
#include <QList>
#include "resident.h"

class Household
{
private:
    int hid;
    int person;
    QString moveIn;
    QString car1;
    QString car2;
    QList<Resident*> familyList;

    bool lightState;   // 전등 상태
    bool curtainState; // 커튼 상태
    bool gasState;     // 가스 상태

public:
    Household(int hid=0, int person=0, QString moveIn="", QString car1="", QString car2="");
    void addFamilyMember(Resident* resident);

    int getHid();
    void setHid(int hid);
    int getPerson();
    void setPerson(int person);
    QString getMoveIn();
    void setMoveIn(const QString &moveIn);
    QString getCar1();
    void setCar1(const QString &car1);
    QString getCar2();
    void setCar2(const QString &car2);
    QList<Resident*> getFamilyList();
    void deleteFamilyMember(Resident *resident);

    void setLightState(bool state);
    bool getLightState();
    void setCurtainState(bool state);
    bool getCurtainState();
    void setGasState(bool state);
    bool getGasState();
};

#endif // HOUSEHOLD_H
