#include "householdmanager.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

HouseholdManager::HouseholdManager(ResidentManager &residentManager)
    : residentList(residentManager.getResidentList()){
    //db연결
    db = QSqlDatabase::addDatabase("QSQLITE", "householdConnection");
    db.setDatabaseName("households.db");

    if(!db.open()){
        qDebug() << "Database connection failed" << db.lastError().text();
    }else{
        qDebug() << "Database connected successfully";

        //테이블 생성
        QSqlQuery query(db);
        query.exec("PRAGMA foreign_keys = ON;");

        QString createHouseholdTableQuery = R"(
            CREATE TABLE IF NOT EXISTS households(
                hid INTEGER PRIMARY KEY,
                person INTEGER,
                moveIn TEXT,
                car1 TEXT,
                car2 TEXT
            );
        )";

        if(!query.exec(createHouseholdTableQuery)){
            qDebug()<<"Failed to create households table:" << query.lastError().text();
            return;
        }

        loadHouseholdsFromDB();

    }
}

HouseholdManager::~HouseholdManager(){
    //db저장
    saveHouseholdsToDB();
    //db닫기
    db.close();
}

void HouseholdManager::saveHouseholdsToDB(){
    QSqlQuery clearHouseholdQuery("DELETE FROM households", db);

    if(!clearHouseholdQuery.exec()){
        qDebug() << "Failed to clear households table:"<<clearHouseholdQuery.lastError().text();
        //return;
    }

    QSqlQuery householdQuery(db);

    for(Household* household : householdList){
        //households 테이블에 데이터 삽입
        householdQuery.prepare("INSERT INTO households (hid, person, moveIn, car1, car2) VALUES (:hid, :person, :moveIn, :car1, :car2)");
        householdQuery.bindValue(":hid", household->getHid());
        householdQuery.bindValue(":person", household->getPerson());
        householdQuery.bindValue(":moveIn", household->getMoveIn());
        householdQuery.bindValue(":car1", household->getCar1());
        householdQuery.bindValue(":car2", household->getCar2());

        if(!householdQuery.exec()){
            qDebug() << "failed to insert households: " << householdQuery.lastError().text();
        }
        householdQuery.clear();
    }
}

void HouseholdManager::loadHouseholdsFromDB(){
    QSqlQuery householdQuery("SELECT hid, person, moveIn, car1, car2 FROM households", db);
    while(householdQuery.next()){
        int hid = householdQuery.value(0).toInt();
        int person = 0;
        QString moveIn = householdQuery.value(2).toString();
        QString car1 = householdQuery.value(3).toString();
        QString car2 = householdQuery.value(4).toString();

        Household *household = new Household(hid, person, moveIn, car1, car2);

        for(Resident* resident : residentList){
            if(resident->getHid() == hid){
                household->addFamilyMember(resident);
            }
        }

        householdList.insert(hid, household);
    }
}

void HouseholdManager::addHousehold(int hid, QString moveIn, QString car1, QString car2){
    Household *household = new Household(hid, 0, moveIn, car1, car2);
    householdList.insert(hid, household);
}

void HouseholdManager::modifyHousehold(int hid, QString moveIn, QString car1, QString car2){
    if(householdList.contains(hid)){
        Household *household = householdList[hid];
        household->setHid(hid);
        household->setMoveIn(moveIn);
        household->setCar1(car1);
        household->setCar2(car2);
    }
}
void HouseholdManager::deleteHousehold(int hid){
    if(householdList.contains(hid)){
        delete householdList.take(hid);
    }
}
QMap<int, Household*> HouseholdManager::getHouseholdList(){
    return householdList;
}

Household* HouseholdManager::searchByHid(int hid){
    return householdList[hid];
}
