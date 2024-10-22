#include "chatwidgetformanager.h"
#include "ui_chatwidgetformanager.h"
#include "chatroomdialog.h"

ChatWidgetForManager::ChatWidgetForManager(Manager* currentManager, ResidentManager* residentManager, HouseholdManager* householdManager, QWidget *parent)
    : QWidget(parent), ui(new Ui::ChatWidgetForManager), currentManager(currentManager), residentManager(residentManager), householdManager(householdManager)
{
    ui->setupUi(this);

    chatRoomListWidget = findChild<QListWidget*>("chatRoomListWidget");
    searchNameButton = findChild<QPushButton*>("searchNameButton");
    createButton = findChild<QPushButton*>("createButton");
    deleteButton = findChild<QPushButton*>("deleteButton");
    searchResultWidget = findChild<QListWidget*>("searchResultWidget");
    selectedResidentWidget = findChild<QListWidget*>("selectedResidentWidget");
    searchNameEdit = findChild<QLineEdit*>("searchNameEdit");

    QIcon searchIcon(":/logoImage/images/search.png");
    searchNameButton->setIcon(searchIcon);
    searchNameButton->setIconSize(QSize(24, 24));
    searchNameEdit->setPlaceholderText("이름을 입력하세요...");

    loadResidentList();
    connect(searchResultWidget, &QListWidget::itemClicked, this, &ChatWidgetForManager::displaySelectedResdient);
    connect(searchNameButton, &QPushButton::clicked, this, &ChatWidgetForManager::searchResidentsByName);
    connect(deleteButton, &QPushButton::clicked, this, &ChatWidgetForManager::deleteSelectedResident);
    connect(createButton, &QPushButton::clicked, this, &ChatWidgetForManager::createChatRoom);
    connect(chatRoomListWidget, &QListWidget::itemDoubleClicked, this, &ChatWidgetForManager::openChatRoomModal);
}

ChatWidgetForManager::~ChatWidgetForManager()
{
    delete ui;
}

void ChatWidgetForManager::loadResidentList(){
    searchResultWidget->clear();

    QMap<int, Resident*> residents = residentManager->getResidentList();
    QMap<int, Resident*>::iterator it;
    for(it = residents.begin(); it!=residents.end(); it++){
        Resident* resident = it.value();
        int rid = resident->getRid();
        searchResultWidget->addItem(resident->getName() + " " + QString::number(rid));
    }
}

void ChatWidgetForManager::createChatRoom(){

    //채팅에 참여할 Resident List를 가져온다
    QList<int> residentRidList; //rid list
    QList<QString> residentNameList; //name list
    int participantCount = selectedResidentWidget->count() + 1; // 참여하는 사람 수

    for (int i = 0; i < participantCount-1; i++) {
        QListWidgetItem* item = selectedResidentWidget->item(i);
        residentNameList.append(item->text().split(" ")[0]);
        residentRidList.append(item->text().split(" ")[1].toInt());
    }

    QList<Resident*> participantList;
    for (int rid : residentRidList){
        Resident* resident = residentManager->getResidentList().value(rid);
        participantList.append(resident);
    }

    /*[TODO] 채팅방 생성
     * currentManager : 현재 로그인된 매니저 객체
     * participantList : 채팅 참여하는 Resdient리스트
     * -> 이들을 다루는 chatManager 객체가 있어야 하고,, chatManager 객체를 chatRoomDialog화면에 넘겨야함(각 채팅방 화면)
    */

    // 채팅방 item 화면 생성
    QWidget *chatRoomWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(chatRoomWidget);

    QLabel *emojiLabel = new QLabel();
    emojiLabel->setPixmap(QPixmap(":/logoImage/images/chatImg.png"));
    layout->addWidget(emojiLabel);

    QLabel *nameLabel = new QLabel(residentNameList.join(", "));
    layout->addWidget(nameLabel);

    QLabel *countLabel = new QLabel(QString::number(participantCount));
    layout->addWidget(countLabel);

    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(10);

    QListWidgetItem *item = new QListWidgetItem(chatRoomListWidget);
    item->setSizeHint(chatRoomWidget->sizeHint());

    chatRoomListWidget->addItem(item);
    chatRoomListWidget->setItemWidget(item, chatRoomWidget);

    // 선택 목록 초기화
    selectedResidentWidget->clear();
}

void ChatWidgetForManager::openChatRoomModal(){
    //채팅방 입장

    //QDialog 창 띄우기
    QDialog* newChatRoomDialog = new ChatRoomDialog(currentManager, this);
    newChatRoomDialog->show();

}

void ChatWidgetForManager::searchResidentsByName(){
    QString part = searchNameEdit->text();
    QList<Resident*> results = residentManager->searchByName(part);
    searchResultWidget->clear();
    for(Resident* resident : results){
        searchResultWidget->addItem(resident->getName()+" " + QString::number(resident->getRid()));
    }
}

void ChatWidgetForManager::displaySelectedResdient(QListWidgetItem *item){
    QString itemText = item->text();
    QStringList parts = itemText.split(" ");
    if(parts.size() == 2){
        int rid = parts[1].toInt();
        Resident* selectedResident = residentManager->getResidentList().value(rid);

        QList<QListWidgetItem*> existingItems = selectedResidentWidget->findItems(selectedResident->getName() + " " + QString::number(selectedResident->getRid()), Qt::MatchExactly);
        if (existingItems.isEmpty()) {  // 중복이 없으면 추가
            selectedResidentWidget->addItem(selectedResident->getName() + " " + QString::number(selectedResident->getRid()));
        }
    }
}

void ChatWidgetForManager::deleteSelectedResident(){
    QListWidgetItem* selectedItem = selectedResidentWidget->currentItem();
    if (selectedItem) {
        delete selectedItem;
    }
}

void ChatWidgetForManager::onResidentListUpdated(){
    loadResidentList();
}
