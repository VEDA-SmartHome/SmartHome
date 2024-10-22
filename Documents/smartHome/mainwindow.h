#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "resident.h"
#include "manager.h"
#include "login.h"
#include "residentmanager.h"
#include "managermanager.h"
#include "householdmanager.h"
#include "residentcontrolwidget.h"
#include "householdcontrolwidget.h"
#include "chatwidgetformanager.h"
#include "residenthomewidget.h"
#include "sensorcontrolwidget.h"
#include "chatwidgetforresident.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void onManagerLoginSuccess(Manager* manager);
    void onResidentLoginSuccess(Resident* resident);
private:
    void setupTabsForResident(Resident* resident);
    void setupTabsForManager(Manager* manager);
    ManagerManager* managerManager;
    ResidentManager* residentManager;
    HouseholdManager* householdManager;
    Login* loginController;

    ResidentControlWidget *residentControlWidget;
    HouseholdControlWidget *householdControlWidget;
    ChatWidgetForManager *chatWidgetForManager;
    ResidentHomeWidget *residentHomeWidget;
    SensorControlWidget *sensorControlWidget;
    ChatWidgetForResident *chatWidgetForResident;
};
#endif // MAINWINDOW_H
