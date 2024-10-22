#ifndef HOUSEHOLDCONTROLWIDGET_H
#define HOUSEHOLDCONTROLWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include "manager.h"
#include "residentmanager.h"
#include "householdmanager.h"

namespace Ui {
class HouseholdControlWidget;
}

class HouseholdControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HouseholdControlWidget(Manager* currentManager, ResidentManager* residentManager,
                                    HouseholdManager* householdManager, QWidget *parent = nullptr);
    ~HouseholdControlWidget();

public slots:
    void searchHouseholdByHid();
    void addHousehold();
    void modifyHousehold();
    void deleteHousehold();
    void displayHouseholdInfo(QListWidgetItem *item);
    void onResidentListUpdated();

private:
    Ui::HouseholdControlWidget *ui;

    Manager* currentManager;
    ResidentManager* residentManager;
    HouseholdManager* householdManager;
    void loadHouseholdList();

    QListWidget* householdListWidget;
    QLineEdit* searchHidEdit;
    QPushButton* searchHidButton;
    QListWidget* searchResultWidget;
    QLineEdit* hidEdit;
    QLineEdit* personEdit;
    QLineEdit* moveInEdit;
    QLineEdit* car1Edit;
    QLineEdit* car2Edit;
    QPushButton* addButton;
    QPushButton* modifyButton;
    QPushButton* deleteButton;
    QListWidget* familyListWidget;
};

#endif // HOUSEHOLDCONTROLWIDGET_H
