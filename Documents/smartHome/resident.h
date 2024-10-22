#ifndef RESIDENT_H
#define RESIDENT_H

#include <QString>
#include <person.h>

class Resident : public Person
{
private:
    int rid; //resident id
    int hid; //household id
    QString phone;
    QString memo;

public:
    Resident(int rid=0, int hid=0, QString name="", QString phone="",
             QString id="", QString pw="", QString memo="");

    int getRid();
    void setRid(int rid);
    int getHid();
    void setHid(int hid);
    QString getPhone();
    void setPhone(const QString &phone);
    QString getMemo();
    void setMemo(const QString &memo);
};

#endif // RESIDENT_H
