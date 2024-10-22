#ifndef RESIDENTCONTROLWIDGET_H
#define RESIDENTCONTROLWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "manager.h"
#include "residentmanager.h"
#include "householdmanager.h"

namespace Ui {
class ResidentControlWidget;
}

class ResidentControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResidentControlWidget(Manager* currentManager, ResidentManager* residentManager,
                                   HouseholdManager* householdManager, QWidget *parent = nullptr);
    ~ResidentControlWidget();

public slots:
    void addResident();
    void deleteResident();
    void searchResidentsByHid();
    void displayResidentInfo(QListWidgetItem *item);
    void onResidentListUpdated();

signals:
    void residentAdded();
    void residentDeleted();

private:
    Ui::ResidentControlWidget *ui;
    Manager* currentManager;
    ResidentManager* residentManager;
    HouseholdManager* householdManager;
    void loadResidentList();

    QListWidget* residentListWidget;
    QListWidget* searchResultWidget;
    QLineEdit* nameEdit;
    QLineEdit* ridEdit;
    QLineEdit* hidEdit;
    QLineEdit* phoneEdit;
    QLineEdit* idEdit;
    QLineEdit* pwEdit;
    QLineEdit* memoEdit;
    QLineEdit* searchHidEdit;
    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* searchHidButton;
    QLabel* profileImage;
};

#endif // RESIDENTCONTROLWIDGET_H
