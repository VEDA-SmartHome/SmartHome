#include "chatwidgetforresident.h"
#include "ui_chatwidgetforresident.h"
#include "chatroomdialog.h"
#include <QDialog>
#include <QMessageBox>

ChatWidgetForResident::ChatWidgetForResident(Resident* currentResident, ManagerManager* managerManager, ResidentManager* residentManager, HouseholdManager* householdManager, QWidget *parent)
    : QWidget(parent), ui(new Ui::ChatWidgetForResident), currentResident(currentResident), managerManager(managerManager), residentManager(residentManager), householdManager(householdManager)
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
    connect(searchResultWidget, &QListWidget::itemClicked, this, &ChatWidgetForResident::displaySelectedResdient);
    connect(searchNameButton, &QPushButton::clicked, this, &ChatWidgetForResident::searchResidentsByName);
    connect(deleteButton, &QPushButton::clicked, this, &ChatWidgetForResident::deleteSelectedResident);
    connect(createButton, &QPushButton::clicked, this, &ChatWidgetForResident::createChatRoom);
    connect(chatRoomListWidget, &QListWidget::itemDoubleClicked, this, &ChatWidgetForResident::openChatRoomModal);
}

ChatWidgetForResident::~ChatWidgetForResident()
{
    delete ui;
}


void ChatWidgetForResident::loadResidentList(){
    searchResultWidget->clear();

    //manager불러오기
    QMap<int, Manager*> managers = managerManager->getManagerList();
    QMap<int, Manager*>::iterator it;
    for(it = managers.begin(); it!=managers.end(); it++){
        Manager* manager = it.value();
        int mid = manager->getMid();
        searchResultWidget->addItem(manager->getName() + " " + QString::number(mid));
    }

    //resident불러오기
    int hid = currentResident->getHid();
    QList<Resident*> residents = (householdManager->searchByHid(hid))->getFamilyList();

    for(Resident* resident : residents){
        if(resident->getRid() == currentResident->getRid()) continue;
        searchResultWidget->addItem(resident->getName() + " " + QString::number(resident->getRid()));
    }
}


void ChatWidgetForResident::createChatRoom(){
    // [예외처리] : 아무도 선택하지 않은 경우
    if (selectedResidentWidget->count() == 0) {
        QMessageBox::warning(this, "채팅방 생성 오류", "참여할 사용자를 선택하세요.");
        return;
    }

    //채팅에 참여할 Resident List를 가져온다
    QList<int> residentRidList; //rid list
    QList<int> managerMidList; //mid list
    QList<QString> residentNameList; //resident name list
    QList<QString> managerNameList; //manager name list
    int participantCount = selectedResidentWidget->count() + 1; // 참여하는 사람 수

    for (int i = 0; i < participantCount-1; i++) {
        QListWidgetItem* item = selectedResidentWidget->item(i);

        if((item->text().split(" ")[0]) == "관리자"){
            managerNameList.append(item->text().split(" ")[0]);
            managerMidList.append(item->text().split(" ")[1].toInt());
        }else{
            residentNameList.append(item->text().split(" ")[0]);
            residentRidList.append(item->text().split(" ")[1].toInt());
        }
    }

    QList<Resident*> participantResidentList;
    QList<Manager*> participantManagerList;

    for(int mid : managerMidList){
        Manager* manager = managerManager->getManagerList().value(mid);
        participantManagerList.append(manager);
    }
    for (int rid : residentRidList){
        Resident* resident = residentManager->getResidentList().value(rid);
        participantResidentList.append(resident);
    }

    /*[TODO] 채팅방 생성
     * currentManager : 현재 로그인된 매니저 객체
     * participantManagerList : 채팅 참여하는 Manager리스트
     * participantResidentList : 채팅 참여하는 Resdient리스트
     * -> 이들을 다루는 chatManager 객체가 있어야 하고,, chatManager 객체를 chatRoomDialog화면에 넘겨야함(각 채팅방 화면)
    */

    // 채팅방 item 화면 생성
    QWidget *chatRoomWidget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(chatRoomWidget);

    QLabel *emojiLabel = new QLabel();
    emojiLabel->setPixmap(QPixmap(":/logoImage/images/chatImg.png"));
    layout->addWidget(emojiLabel);

    QString residentNames = residentNameList.join(", ");
    QString managerNames = managerNameList.join(", ");

    // 두 리스트를 결합하여 최종 문자열 생성
    QString combinedNames = residentNames;
    if (!managerNames.isEmpty()) {  // managerNames가 비어있지 않으면 쉼표로 구분하여 추가
        if (!residentNames.isEmpty()) {
            combinedNames += ", ";  // residentNames도 있으면 쉼표 추가
        }
        combinedNames += managerNames;
    }

    // QLabel에 출력
    QLabel *nameLabel = new QLabel(combinedNames);
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

void ChatWidgetForResident::openChatRoomModal(){
    //채팅방 입장

    //QDialog 창 띄우기
    QDialog* newChatRoomDialog = new ChatRoomDialog(currentResident, this);
    newChatRoomDialog->show();

}

void ChatWidgetForResident::searchResidentsByName(){
    QString part = searchNameEdit->text();
    QList<Manager*> resultsManager = managerManager->searchByName(part);
    QList<Resident*> resultsResident;

    int hid = currentResident->getHid();
    QList<Resident*> residents = (householdManager->searchByHid(hid))->getFamilyList();

    for(Resident* resident : residents){//familylist에서 이름으로 검색
        if(resident->getName().contains(part, Qt::CaseInsensitive)){
            resultsResident.append(resident);
        }
    }

    searchResultWidget->clear();
    for(Manager* manager : resultsManager){
        searchResultWidget->addItem(manager->getName()+" " + QString::number(manager->getMid()));
    }
    for(Resident* resident : resultsResident){
        searchResultWidget->addItem(resident->getName()+" " + QString::number(resident->getRid()));
    }
}

void ChatWidgetForResident::displaySelectedResdient(QListWidgetItem *item){
    QString itemText = item->text();
    QStringList parts = itemText.split(" ");
    if(parts.size() == 2){
        if(parts[0] == "관리자"){//관리자 선택
            int mid = parts[1].toInt();
            Manager* selectedManager = managerManager->getManagerList().value(mid);

            QList<QListWidgetItem*> existingItems = selectedResidentWidget->findItems(selectedManager->getName() + " " + QString::number(selectedManager->getMid()), Qt::MatchExactly);
            if (existingItems.isEmpty()) {  // 중복이 없으면 추가
                selectedResidentWidget->addItem(selectedManager->getName() + " " + QString::number(selectedManager->getMid()));
            }
        }else{//거주자 선택
            int rid = parts[1].toInt();
            Resident* selectedResident = residentManager->getResidentList().value(rid);

            QList<QListWidgetItem*> existingItems = selectedResidentWidget->findItems(selectedResident->getName() + " " + QString::number(selectedResident->getRid()), Qt::MatchExactly);
            if (existingItems.isEmpty()) {  // 중복이 없으면 추가
                selectedResidentWidget->addItem(selectedResident->getName() + " " + QString::number(selectedResident->getRid()));
            }
        }
    }
}

void ChatWidgetForResident::deleteSelectedResident(){
    QListWidgetItem* selectedItem = selectedResidentWidget->currentItem();
    if (selectedItem) {
        delete selectedItem;
    }
}

void ChatWidgetForResident::onResidentListUpdated(){
    loadResidentList();
}

