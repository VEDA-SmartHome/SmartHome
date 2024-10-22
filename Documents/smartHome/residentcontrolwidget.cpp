#include "residentcontrolwidget.h"
#include "ui_residentcontrolwidget.h"
#include <QMap>
#include <QList>

ResidentControlWidget::ResidentControlWidget(Manager* currentManager, ResidentManager* residentManager, HouseholdManager* householdManager, QWidget *parent)
    : QWidget(parent), ui(new Ui::ResidentControlWidget), currentManager(currentManager), residentManager(residentManager), householdManager(householdManager){
    ui->setupUi(this);

    residentListWidget = findChild<QListWidget*>("residentListWidget");
    searchResultWidget = findChild<QListWidget*>("searchResultWidget");
    nameEdit = findChild<QLineEdit*>("nameEdit");
    ridEdit = findChild<QLineEdit*>("ridEdit");
    ridEdit->setReadOnly(true);
    hidEdit = findChild<QLineEdit*>("hidEdit");
    phoneEdit = findChild<QLineEdit*>("phoneEdit");
    idEdit = findChild<QLineEdit*>("idEdit");
    pwEdit = findChild<QLineEdit*>("pwEdit");
    memoEdit = findChild<QLineEdit*>("memoEdit");
    addButton = findChild<QPushButton*>("addButton");
    deleteButton = findChild<QPushButton*>("deleteButton");
    searchHidEdit = findChild<QLineEdit*>("searchHidEdit");
    searchHidButton = findChild<QPushButton*>("searchHidButton");
    profileImage = findChild<QLabel*>("profileImage");

    QIcon searchIcon(":/logoImage/images/search.png");
    searchHidButton->setIcon(searchIcon);
    searchHidButton->setIconSize(QSize(24, 24));
    QPixmap pixmap(":/logoImage/images/profile.png");
    profileImage->setPixmap(pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    searchHidEdit->setPlaceholderText("hid를 입력하세요...");


    loadResidentList();
    connect(residentListWidget, &QListWidget::itemClicked, this, &ResidentControlWidget::displayResidentInfo);
    connect(searchResultWidget, &QListWidget::itemClicked, this, &ResidentControlWidget::displayResidentInfo);
    connect(addButton, &QPushButton::clicked, this, &ResidentControlWidget::addResident);
    connect(deleteButton, &QPushButton::clicked, this, &ResidentControlWidget::deleteResident);
    connect(searchHidButton, &QPushButton::clicked, this, &ResidentControlWidget::searchResidentsByHid);
}

ResidentControlWidget::~ResidentControlWidget()
{
    delete ui;
}


void ResidentControlWidget::loadResidentList(){
    residentListWidget->clear();

    QMap<int, Resident*> residents = residentManager->getResidentList();
    QMap<int, Resident*>::iterator it;
    for(it = residents.begin(); it!=residents.end(); it++){
        Resident* resident = it.value();
        int rid = resident->getRid();
        residentListWidget->addItem(resident->getName() + " " + QString::number(rid));
    }
}

void ResidentControlWidget::addResident(){
    int hid = hidEdit->text().toInt();
    QString name = nameEdit->text();
    QString phone = phoneEdit->text();
    QString id = idEdit->text();
    QString pw = pwEdit->text();
    QString memo = memoEdit->text();

    Resident* resident = residentManager->addResident(hid, name, phone, id, pw, memo);
    householdManager->searchByHid(hid)->addFamilyMember(resident);
    loadResidentList();
    searchResultWidget->clear();

    ridEdit->clear();
    hidEdit->clear();
    nameEdit->clear();
    phoneEdit->clear();
    idEdit->clear();
    pwEdit->clear();
    memoEdit->clear();

    emit residentAdded();
}

void ResidentControlWidget::deleteResident(){
    int rid = ridEdit->text().toInt();

    Resident* deletedResident = residentManager->getResidentList().value(rid);
    int hid = deletedResident->getHid();

    Household* deletedHousehold = householdManager->searchByHid(hid);
    deletedHousehold->setPerson(deletedHousehold->getPerson()-1);
    deletedHousehold->deleteFamilyMember(deletedResident);

    residentManager->deleteResident(rid);

    ridEdit->clear();
    hidEdit->clear();
    nameEdit->clear();
    phoneEdit->clear();
    idEdit->clear();
    pwEdit->clear();
    memoEdit->clear();
    loadResidentList();
    searchResultWidget->clear();

    emit residentDeleted();
}

void ResidentControlWidget::searchResidentsByHid(){
    int hid = searchHidEdit->text().toInt();
    QList<Resident*> results = (householdManager->searchByHid(hid))->getFamilyList();

    searchResultWidget->clear();
    for(Resident* resident : results){
        searchResultWidget->addItem(resident->getName()+" " + QString::number(resident->getRid()));
    }

}

void ResidentControlWidget::displayResidentInfo(QListWidgetItem *item){
    QString itemText = item->text();
    QStringList parts = itemText.split(" ");
    if(parts.size() == 2){
        QString ridStr = parts[1];
        int rid = ridStr.toInt();
        Resident* selectedResident = residentManager->getResidentList().value(rid);
        //정보표시
        nameEdit->setText(selectedResident->getName());
        ridEdit->setText(QString::number(selectedResident->getRid()));
        hidEdit->setText(QString::number(selectedResident->getHid()));
        phoneEdit->setText(selectedResident->getPhone());
        idEdit->setText(selectedResident->getId());
        pwEdit->setText(selectedResident->getPw());
        memoEdit->setText(selectedResident->getMemo());
    }
}

void ResidentControlWidget::onResidentListUpdated(){
    loadResidentList();
}

