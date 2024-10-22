#include "householdcontrolwidget.h"
#include "ui_householdcontrolwidget.h"
#include "resident.h"

HouseholdControlWidget::HouseholdControlWidget(Manager* currentManager, ResidentManager* residentManager, HouseholdManager* householdManager, QWidget *parent)
    : QWidget(parent), ui(new Ui::HouseholdControlWidget), currentManager(currentManager), residentManager(residentManager), householdManager(householdManager)
{
    ui->setupUi(this);
    householdListWidget = findChild<QListWidget*>("householdListWidget");
    searchHidEdit = findChild<QLineEdit*>("searchHidEdit");
    searchHidButton = findChild<QPushButton*>("searchHidButton");
    searchResultWidget = findChild<QListWidget*>("searchResultWidget");
    hidEdit = findChild<QLineEdit*>("hidEdit");
    personEdit = findChild<QLineEdit*>("personEdit");
    personEdit->setReadOnly(true);
    moveInEdit = findChild<QLineEdit*>("moveInEdit");
    car1Edit = findChild<QLineEdit*>("car1Edit");
    car2Edit = findChild<QLineEdit*>("car2Edit");
    addButton = findChild<QPushButton*>("addButton");
    modifyButton = findChild<QPushButton*>("modifyButton");
    deleteButton = findChild<QPushButton*>("deleteButton");
    familyListWidget = findChild<QListWidget*>("familyListWidget");

    QIcon searchIcon(":/logoImage/images/search.png");
    searchHidButton->setIcon(searchIcon);
    searchHidButton->setIconSize(QSize(24, 24));
    searchHidEdit->setPlaceholderText("hid를 입력하세요...");

    loadHouseholdList();
    connect(householdListWidget, &QListWidget::itemClicked, this, &HouseholdControlWidget::displayHouseholdInfo);
    connect(searchResultWidget, &QListWidget::itemClicked, this, &HouseholdControlWidget::displayHouseholdInfo);
    connect(searchHidButton, &QPushButton::clicked, this, &HouseholdControlWidget::searchHouseholdByHid);
    connect(addButton, &QPushButton::clicked, this, &HouseholdControlWidget::addHousehold);
    connect(modifyButton, &QPushButton::clicked, this, &HouseholdControlWidget::modifyHousehold);
    connect(deleteButton, &QPushButton::clicked, this, &HouseholdControlWidget::deleteHousehold);
}

HouseholdControlWidget::~HouseholdControlWidget()
{
    delete ui;
}

void HouseholdControlWidget::loadHouseholdList(){
    householdListWidget->clear();
    QMap<int, Household*> households = householdManager->getHouseholdList();
    QMap<int, Household*>::iterator it;
    for(it = households.begin(); it!=households.end(); it++){
        Household* household = it.value();
        int hid = household->getHid();
        householdListWidget->addItem(QString::number(hid) + " " + QString::number(household->getPerson()));
    }
}

void HouseholdControlWidget::searchHouseholdByHid(){
    int hid = searchHidEdit->text().toInt();
    Household* result = householdManager->searchByHid(hid);
    searchResultWidget->clear();
    searchResultWidget->addItem(QString::number(result->getHid()) + " " + QString::number(result->getPerson()));
}

void HouseholdControlWidget::addHousehold(){
    int hid = hidEdit->text().toInt();
    QString moveIn = moveInEdit->text();
    QString car1 = car1Edit->text();
    QString car2 = car2Edit->text();

    householdManager->addHousehold(hid, moveIn, car1, car2);
    loadHouseholdList();
    searchResultWidget->clear();

    hidEdit->clear();
    personEdit->clear();
    moveInEdit->clear();
    car1Edit->clear();
    car2Edit->clear();
    familyListWidget->clear();
}

void HouseholdControlWidget::modifyHousehold(){
    int hid = hidEdit->text().toInt();
    QString moveIn = moveInEdit->text();
    QString car1 = car1Edit->text();
    QString car2 = car2Edit->text();

    householdManager->modifyHousehold(hid, moveIn, car1, car2);
    loadHouseholdList();
    searchResultWidget->clear();
    hidEdit->clear();
    personEdit->clear();
    moveInEdit->clear();
    car1Edit->clear();
    car2Edit->clear();
    familyListWidget->clear();
}

void HouseholdControlWidget::deleteHousehold(){
    int hid = hidEdit->text().toInt();
    householdManager->deleteHousehold(hid);

    loadHouseholdList();
    searchResultWidget->clear();
    hidEdit->clear();
    personEdit->clear();
    moveInEdit->clear();
    car1Edit->clear();
    car2Edit->clear();
    familyListWidget->clear();
}

void HouseholdControlWidget::displayHouseholdInfo(QListWidgetItem *item){

    QString itemText = item->text();
    QStringList parts = itemText.split(" ");
    if(parts.size() == 2){
        QString hidStr = parts[0];
        int hid = hidStr.toInt();
        Household* selectedHousehold = householdManager->searchByHid(hid);
        hidEdit->setText(QString::number(selectedHousehold->getHid()));
        personEdit->setText(QString::number(selectedHousehold->getPerson()));
        moveInEdit->setText(selectedHousehold->getMoveIn());
        car1Edit->setText(selectedHousehold->getCar1());
        car2Edit->setText(selectedHousehold->getCar2());

        familyListWidget->clear();
        QList<Resident*> familyList = selectedHousehold->getFamilyList();
        for(Resident* resident : familyList){
            familyListWidget->addItem(resident->getName() + " " + QString::number(hid));
        }
    }
}

void HouseholdControlWidget::onResidentListUpdated(){
    loadHouseholdList();
}
