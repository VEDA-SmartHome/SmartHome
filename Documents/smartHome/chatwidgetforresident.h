#ifndef CHATWIDGETFORRESIDENT_H
#define CHATWIDGETFORRESIDENT_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include "residentmanager.h"
#include "householdmanager.h"
#include "managermanager.h"
#include "resident.h"

namespace Ui {
class ChatWidgetForResident;
}

class ChatWidgetForResident : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidgetForResident(Resident* currentResident, ManagerManager* managerManager, ResidentManager* residentManager,
                                   HouseholdManager* householdManager, QWidget *parent = nullptr);
    ~ChatWidgetForResident();

public slots:
    void createChatRoom();
    void searchResidentsByName();
    void displaySelectedResdient(QListWidgetItem *item);
    void deleteSelectedResident();
    void openChatRoomModal();
    void onResidentListUpdated();


private:
    Ui::ChatWidgetForResident *ui;
    Resident* currentResident;
    ManagerManager* managerManager;
    ResidentManager* residentManager;
    HouseholdManager* householdManager;

    void loadResidentList();

    QListWidget* chatRoomListWidget;
    QPushButton* searchNameButton;
    QPushButton* createButton;
    QPushButton* deleteButton;
    QListWidget* searchResultWidget;
    QListWidget* selectedResidentWidget;
    QLineEdit* searchNameEdit;

};

#endif // CHATWIDGETFORRESIDENT_H
