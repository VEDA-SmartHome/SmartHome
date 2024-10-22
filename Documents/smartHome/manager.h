#ifndef MANAGER_H
#define MANAGER_H

#include <QString>
#include "person.h"

class Manager : public Person
{
private:
    int mid;

public:
    Manager(QString id, QString pw);

    int getMid();
    void setMid(int id);
};

#endif // MANAGER_H
