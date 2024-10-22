#ifndef SENSORCONTROLWIDGET_H
#define SENSORCONTROLWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "resident.h"
#include "residentmanager.h"
#include "householdmanager.h"

namespace Ui {
class SensorControlWidget;
}

class SensorControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SensorControlWidget(Resident* currentResident, ResidentManager* residentManager,
                                 HouseholdManager* householdManager, QWidget *parent = nullptr);
    ~SensorControlWidget();

public slots:
    void toggleLightState(bool checked);
    void toggleCurtainState(bool checked);
    void toggleGasState(bool checked);
    void startStreaming();

private:
    Ui::SensorControlWidget *ui;
    Resident* currentResident;
    ResidentManager* residentManager;
    HouseholdManager* householdManager;

    QLabel* lightImg;
    QPushButton* lightButton;
    QLabel* curtainImg;
    QPushButton* curtainButton;
    QLabel* gasImg;
    QPushButton* gasButton;
    QLabel* cctvImg;
    QPushButton* cctvButton;
};

#endif // SENSORCONTROLWIDGET_H
