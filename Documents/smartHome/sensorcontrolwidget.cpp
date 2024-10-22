#include "sensorcontrolwidget.h"
#include "ui_sensorcontrolwidget.h"

SensorControlWidget::SensorControlWidget(Resident* currentResident, ResidentManager* residentManager, HouseholdManager* householdManager, QWidget *parent)
    : QWidget(parent), ui(new Ui::SensorControlWidget), currentResident(currentResident), residentManager(residentManager), householdManager(householdManager)
{
    ui->setupUi(this);

    lightButton = findChild<QPushButton*>("lightButton");
    curtainButton = findChild<QPushButton*>("curtainButton");
    gasButton = findChild<QPushButton*>("gasButton");
    cctvButton = findChild<QPushButton*>("cctvButton");

    QLabel* lightImg = findChild<QLabel*>("lightImg");
    QPixmap pixmap(":/logoImage/images/light.png");
    lightImg->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLabel* curtainImg = findChild<QLabel*>("curtainImg");
    QPixmap pixmap2(":/logoImage/images/curtain.png");
    curtainImg->setPixmap(pixmap2.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLabel* gasImg = findChild<QLabel*>("gasImg");
    QPixmap pixmap3(":/logoImage/images/gas.png");
    gasImg->setPixmap(pixmap3.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    QLabel* cctvImg = findChild<QLabel*>("cctvImg");
    QPixmap pixmap4(":/logoImage/images/cctv.png");
    cctvImg->setPixmap(pixmap4.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    connect(lightButton, &QPushButton::toggled, this, &SensorControlWidget::toggleLightState);
    connect(curtainButton, &QPushButton::toggled, this, &SensorControlWidget::toggleCurtainState);
    connect(gasButton, &QPushButton::toggled, this, &SensorControlWidget::toggleGasState);
    connect(cctvButton, &QPushButton::clicked, this, &SensorControlWidget::startStreaming);
}

SensorControlWidget::~SensorControlWidget()
{
    delete ui;
}

void SensorControlWidget::toggleLightState(bool checked){
    Household* household = householdManager->searchByHid(currentResident->getHid());
    if (household) {
        household->setLightState(checked);
    }
}

void SensorControlWidget::toggleCurtainState(bool checked){
    Household* household = householdManager->searchByHid(currentResident->getHid());
    if (household) {
        household->setCurtainState(checked);
    }
}

void SensorControlWidget::toggleGasState(bool checked){
    Household* household = householdManager->searchByHid(currentResident->getHid());
    if (household) {
        household->setGasState(checked);
    }
}

void SensorControlWidget::startStreaming(){
    //TODO : cctv 스트리밍 시작
}

