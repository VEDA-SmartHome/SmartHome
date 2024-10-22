#include "person.h"

Person::Person(QString id, QString pw, QString name) : id(id), pw(pw), name(name) {}

QString Person::getId() { return id; }
void Person::setId(const QString &id) { this->id = id; }

QString Person::getPw() { return pw; }
void Person::setPw(const QString &pw) { this->pw = pw; }

QString Person::getName() { return name; }
void Person::setName(const QString &name) { this->name = name; }

