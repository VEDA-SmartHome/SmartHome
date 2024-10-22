#ifndef CHATROOMDIALOG_H
#define CHATROOMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>

#include "person.h"

namespace Ui {
class ChatRoomDialog;
}

class ChatRoomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatRoomDialog(Person* person, QWidget *parent = nullptr); //TODO : 추가
    ~ChatRoomDialog();

public slots:
    //TODO

private:
    Ui::ChatRoomDialog *ui;

    //TODO
    Person* currentUser;

    //ui
    QLabel* chatRoomName;
    QLabel* participantCount;
    QPushButton* getOutButton;
    QListWidget* chatListWidget;
    QLineEdit* chatInputWidget;
    QPushButton* sendButton;
    QPushButton* fileButton;
    QListWidget* participantListWidget;
    QListWidget* savedChatMessageWidget;
    QPushButton* searchMsgButton;
    QLineEdit* searchMsgEdit;
    QLabel* chatRoomImg;

    //TODO
    void loadParticipantListWidget();
};

#endif // CHATROOMDIALOG_H
