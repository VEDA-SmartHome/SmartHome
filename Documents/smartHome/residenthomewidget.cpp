#include "residenthomewidget.h"
#include "ui_residenthomewidget.h"

ResidentHomeWidget::ResidentHomeWidget(Resident* currentResident, ResidentManager* residentManager, HouseholdManager* householdManager, QWidget *parent)
    : QWidget(parent), ui(new Ui::ResidentHomeWidget), currentResident(currentResident), residentManager(residentManager), householdManager(householdManager)
{
    ui->setupUi(this);

    residentListWidget = findChild<QListWidget*>("residentListWidget");
    hidLabel = findChild<QLabel*>("hidLabel");
    nameEdit = findChild<QLineEdit*>("nameEdit");
    hidEdit = findChild<QLineEdit*>("hidEdit");
    phoneEdit = findChild<QLineEdit*>("phoneEdit");
    idEdit = findChild<QLineEdit*>("idEdit");
    pwEdit = findChild<QLineEdit*>("pwEdit");
    modifyButton = findChild<QPushButton*>("modifyButton");

    QLabel* homeLogo = findChild<QLabel*>("homeLogo");
    QPixmap pixmap(":/logoImage/images/HOME.png");
    homeLogo->setPixmap(pixmap.scaled(200, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    QLabel* profileImg = findChild<QLabel*>("profileImg");
    QPixmap pixmap2(":/logoImage/images/profile.png");
    profileImg->setPixmap(pixmap2.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    loadResidentInfo();
    loadPersonalInfo();
    connect(modifyButton, &QPushButton::clicked, this, &ResidentHomeWidget::modifyResidentInfo);
}

ResidentHomeWidget::~ResidentHomeWidget()
{
    delete ui;
}

void ResidentHomeWidget::loadResidentInfo(){
    int hid = currentResident->getHid();
    Household* currentHousehold = householdManager->searchByHid(hid);
    QList<Resident*> residents = currentHousehold->getFamilyList();
    for(Resident* resident : residents){
        residentListWidget->addItem(resident->getName() + " " + QString::number(hid));
    }
}

void ResidentHomeWidget::loadPersonalInfo(){
    nameEdit->setText(currentResident->getName());
    hidEdit->setText(QString::number(currentResident->getHid()));
    phoneEdit->setText(currentResident->getPhone());
    idEdit->setText(currentResident->getId());
    pwEdit->setText(currentResident->getPw());
}

void ResidentHomeWidget::modifyResidentInfo(){
    int rid = currentResident->getRid();
    int hid = hidEdit->text().toInt();
    QString name = nameEdit->text();
    QString phone = phoneEdit->text();
    QString id = idEdit->text();
    QString pw = pwEdit->text();

    residentManager->modifyResident(rid, hid, name, phone, id, pw);
    loadPersonalInfo();
}

void ResidentHomeWidget::onResidentListUpdated(){
    loadResidentInfo();
}
