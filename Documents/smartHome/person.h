#ifndef PERSON_H
#define PERSON_H

#include <QString>

class Person {
protected:
    QString id;
    QString pw;
    QString name;

public:
    Person(QString id = "", QString pw = "", QString name = "");


    QString getId();
    void setId(const QString &id);

    QString getPw();
    void setPw(const QString &pw);
    QString getName();
    void setName(const QString &name);
};

#endif // PERSON_H
