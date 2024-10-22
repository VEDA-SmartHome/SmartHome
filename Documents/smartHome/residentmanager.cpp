#include "residentmanager.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

ResidentManager::ResidentManager() {
    //db연결
    db = QSqlDatabase::addDatabase("QSQLITE", "residentConnection");
    db.setDatabaseName("residents.db");

    if(!db.open()){
        qDebug() << "Database connection failed" << db.lastError().text();
    }else{
        qDebug() << "Database connected successfully";
        QSqlQuery query(db);

        QString createResidentsQuery = R"(
            CREATE TABLE IF NOT EXISTS residents (
                rid INTEGER PRIMARY KEY,
                hid INTEGER,
                name TEXT,
                phone TEXT,
                id TEXT,
                pw TEXT,
                memo TEXT
            );
        )";

        if(!query.exec(createResidentsQuery)){
            qDebug()<<"Failed to create residents table:" << query.lastError().text();
            return;
        }
        loadResidentsFromDB();
    }

}

ResidentManager::~ResidentManager(){
    //db저장
    saveResidentsToDB();
    //db닫기
    db.close();
}

void ResidentManager::loadResidentsFromDB(){
    //db로드
    QSqlQuery query("SELECT rid, hid, name, phone, id, pw, memo FROM residents", db);
    while(query.next()){
        int rid = query.value(0).toInt();
        int hid = query.value(1).toInt();
        QString name = query.value(2).toString();
        QString phone = query.value(3).toString();
        QString id = query.value(4).toString();
        QString pw = query.value(5).toString();
        QString memo = query.value(6).toString();

        Resident *resident = new Resident(rid, hid, name, phone, id, pw, memo);
        residentList.insert(rid, resident);
    }
}

void ResidentManager::saveResidentsToDB(){
    QSqlQuery clearQuery("DELETE FROM residents", db);

    if(!clearQuery.exec()){
        qDebug() << "Failed to clear residents table:"<<clearQuery.lastError().text();
        //return;
    }

    QSqlQuery query(db);

    for (Resident* resident : residentList) {
        query.prepare("INSERT INTO residents(rid, hid, name, phone, id, pw, memo) VALUES (:rid, :hid, :name, :phone, :id, :pw, :memo)");
        query.bindValue(":rid", resident->getRid());
        query.bindValue(":hid", resident->getHid());
        query.bindValue(":name", resident->getName());
        query.bindValue(":phone", resident->getPhone());
        query.bindValue(":id", resident->getId());
        query.bindValue(":pw", resident->getPw());
        query.bindValue(":memo", resident->getMemo());

        if(!query.exec()){
            qDebug() << "Failed to insert resident:" << query.lastError().text();
        }

        query.clear();
    }
}

Resident* ResidentManager::addResident(int hid, QString name, QString phone, QString id, QString pw, QString memo){
    int rid = makeRid();
    Resident *resident = new Resident(rid, hid, name, phone, id, pw, memo);
    residentList.insert(rid, resident);
    return resident;
}

int ResidentManager::makeRid(){
    if (residentList.empty()) {
        return 0;
    } else {
        auto it = residentList.end();
        int lastId = (--it).key();
        return (++lastId);
    }
}

void ResidentManager::modifyResident(int rid, int hid, QString name, QString phone, QString id, QString pw){
    if(residentList.contains(rid)){
        Resident *resident = residentList[rid];
        resident->setHid(hid);
        resident->setName(name);
        resident->setPhone(phone);
        resident->setId(id);
        resident->setPw(pw);
    }
}

void ResidentManager::deleteResident(int rid){
    if(residentList.contains(rid)){
        Resident *resident = residentList.take(rid);
        if(resident){
            delete resident;
            qDebug() << "delete resident";
        }
    }
}

QMap<int, Resident*> ResidentManager::getResidentList(){
    return residentList;
}

QList<Resident*> ResidentManager::searchByName(const QString &namePart){
    QList<Resident*> result;

    for(Resident* resident : residentList){
        if(resident->getName().contains(namePart, Qt::CaseInsensitive)){
            result.append(resident);
        }
    }
    return result;
}
