#ifndef RESIDENTHOMEWIDGET_H
#define RESIDENTHOMEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>

#include "resident.h"
#include "householdmanager.h"
#include "residentmanager.h"

namespace Ui {
class ResidentHomeWidget;
}

class ResidentHomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResidentHomeWidget(Resident* currentResident, ResidentManager* residentManager,
                                HouseholdManager* householdManager, QWidget *parent = nullptr);
    ~ResidentHomeWidget();

signals:
    void residentModified();

public slots:
    void modifyResidentInfo();
    void onResidentListUpdated();

private:
    Ui::ResidentHomeWidget *ui;
    Resident* currentResident;
    ResidentManager* residentManager;
    HouseholdManager* householdManager;

    QLabel* hidLabel;
    QListWidget* residentListWidget;
    QLineEdit* nameEdit;
    QLineEdit* hidEdit;
    QLineEdit* phoneEdit;
    QLineEdit* idEdit;
    QLineEdit* pwEdit;
    QPushButton* modifyButton;

    void loadResidentInfo();
    void loadPersonalInfo();
};

#endif // RESIDENTHOMEWIDGET_H
