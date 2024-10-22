#include "chatroomdialog.h"
#include "ui_chatroomdialog.h"

ChatRoomDialog::ChatRoomDialog(Person* currentUser, QWidget *parent)
    : QDialog(parent), ui(new Ui::ChatRoomDialog), currentUser(currentUser)
{
    ui->setupUi(this);

    chatRoomImg = findChild<QLabel*>("chatRoomImg");
    QPixmap pixmap(":/logoImage/images/chatImg.png");
    chatRoomImg->setPixmap(pixmap);

    chatRoomName = findChild<QLabel*>("chatRoomName");
    participantCount = findChild<QLabel*>("participantCount");
    getOutButton = findChild<QPushButton*>("getOutButton");
    chatListWidget = findChild<QListWidget*>("chatListWidget");
    chatInputWidget = findChild<QLineEdit*>("chatInputWidget");
    sendButton = findChild<QPushButton*>("sendButton");
    fileButton = findChild<QPushButton*>("fileButton");
    participantListWidget = findChild<QListWidget*>("participantListWidget");
    savedChatMessageWidget = findChild<QListWidget*>("savedChatMessageWidget");
    searchMsgButton = findChild<QPushButton*>("searchMsgButton");
    searchMsgEdit = findChild<QLineEdit*>("searchMsgEdit");

    loadParticipantListWidget();
    //TODO
    /*
    connect(searchMsgButton, &QPushButton::clicked, this, &ChatRoomDialog::"savedChatMessageWidget에 검색된 메시지를 띄우는 슬롯 구현");
    connect(fileButton, &QPushButton::clicked, this, &ChatRoomDialog::"파일 전송 슬롯 구현");
    connect(sendButton, &QPushButoon::clicked, this, &ChatRoomDialog::"채팅 전송 슬롯 구현");
    connect(getOutButton, &QPushButton::clicked, this, &chatRoomDialog::"채팅방 나가기 슬롯 구현 + 시그널 발생시켜서 + chatWidgetForManager에서 채팅방 삭제");
    */
}

ChatRoomDialog::~ChatRoomDialog()
{
    delete ui;
}

void ChatRoomDialog::loadParticipantListWidget(){
    //TODO (현재 참여자 리스트 띄우기)
    /*
    QMap<int, Resident*> participantList = ...; //참여자리스트
    Manager* currentManager = ...; //현재 로그인된 manager객체
    QMap<int, Resident*>::iterator it;
    for(it = participantList.begin(); it!=participantList.end(); it++){
        Resident* resident = it.value();
        int hid = resident->getHid();
        participantListWidget->addItem(resident->getName() + " " + QString::number(hid));
    }
    */
}
