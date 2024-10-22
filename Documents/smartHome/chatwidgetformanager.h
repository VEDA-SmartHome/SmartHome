#ifndef CHATWIDGETFORMANAGER_H
#define CHATWIDGETFORMANAGER_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include "manager.h"
#include "residentmanager.h"
#include "householdmanager.h"

namespace Ui {
class ChatWidgetForManager;
}

class ChatWidgetForManager : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidgetForManager(Manager* currentManager, ResidentManager* residentManager,
                                  HouseholdManager* householdManager, QWidget *parent = nullptr);
    ~ChatWidgetForManager();

public slots:
    void createChatRoom();
    void searchResidentsByName();
    void displaySelectedResdient(QListWidgetItem *item);
    void deleteSelectedResident();
    void openChatRoomModal();
    void onResidentListUpdated();

private:
    Ui::ChatWidgetForManager *ui;
    Manager* currentManager;
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

#endif // CHATWIDGETFORMANAGER_H
