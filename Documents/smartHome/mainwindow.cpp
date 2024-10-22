#include "mainwindow.h"
#include "loginwidget.h"
#include <QTabWidget>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setStyleSheet("MainWindow { background-color: rgb(255, 242, 204); }");
    managerManager = new ManagerManager();
    residentManager = new ResidentManager();
    householdManager = new HouseholdManager(*residentManager);
    loginController = new Login(managerManager, residentManager);

    LoginWidget *loginWidget = new LoginWidget(loginController, this);
    setCentralWidget(loginWidget);

    connect(loginWidget, &LoginWidget::managerLoginSuccess, this, &MainWindow::onManagerLoginSuccess);
    connect(loginWidget, &LoginWidget::residentLoginSuccess, this, &MainWindow::onResidentLoginSuccess);

}

MainWindow::~MainWindow()
{

}

void MainWindow::onManagerLoginSuccess(Manager *manager){//관리자 로그인 성공
    //로그아웃, exit 메뉴바 설정
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *logoutMenu = menuBar->addMenu("LOGOUT");
    QMenu *exitMenu = menuBar->addMenu("EXIT");

    QAction *logoutAction = new QAction("LOGOUT", this);
    logoutMenu->addAction(logoutAction);
    QAction *exitAction = new QAction("EXIT", this);
    exitMenu->addAction(exitAction);

    connect(logoutAction, &QAction::triggered, this, [=](){
        LoginWidget *loginWidget = new LoginWidget(loginController, this);
        setMenuBar(nullptr); //menubar제거
        setCentralWidget(loginWidget);
        connect(loginWidget, &LoginWidget::managerLoginSuccess, this, &MainWindow::onManagerLoginSuccess);
        connect(loginWidget, &LoginWidget::residentLoginSuccess, this, &MainWindow::onResidentLoginSuccess);
    });
    connect(exitAction, &QAction::triggered, this, [=](){
        if (residentManager) {
            delete residentManager;
        }
        if (householdManager) {
            delete householdManager;
        }
        if (managerManager) {
            delete managerManager;
        }
        QApplication::quit();
    });
    this->setMenuBar(menuBar);

    //기능화면 탭 설정
    setupTabsForManager(manager);
}

void MainWindow::onResidentLoginSuccess(Resident *resident){//거주자 로그인 성공
    //로그아웃, exit 메뉴바 설정
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *logoutMenu = menuBar->addMenu("LOGOUT");
    QMenu *exitMenu = menuBar->addMenu("EXIT");

    QAction *logoutAction = new QAction("LOGOUT", this);
    logoutMenu->addAction(logoutAction);
    QAction *exitAction = new QAction("EXIT", this);
    exitMenu->addAction(exitAction);

    connect(logoutAction, &QAction::triggered, this, [=](){
        LoginWidget *loginWidget = new LoginWidget(loginController, this);
        setMenuBar(nullptr); //menubar제거
        setCentralWidget(loginWidget);
        connect(loginWidget, &LoginWidget::managerLoginSuccess, this, &MainWindow::onManagerLoginSuccess);
        connect(loginWidget, &LoginWidget::residentLoginSuccess, this, &MainWindow::onResidentLoginSuccess);
    });
    connect(exitAction, &QAction::triggered, this, [=](){
        if (residentManager) {
            delete residentManager;
        }
        if (householdManager) {
            delete householdManager;
        }
        if (managerManager) {
            delete managerManager;
        }
        QApplication::quit();
    });
    this->setMenuBar(menuBar);

    //기능화면 탭설정
    setupTabsForResident(resident);
}

void MainWindow::setupTabsForManager(Manager *manager){
    //탭위젯 생성, 위젯 스택 생성
    QTabWidget *tabWidget = new QTabWidget(this);
    residentControlWidget = new ResidentControlWidget(manager, residentManager, householdManager, this);
    householdControlWidget = new HouseholdControlWidget(manager, residentManager, householdManager, this);
    chatWidgetForManager = new ChatWidgetForManager(manager, residentManager, householdManager, this);

    tabWidget->addTab(residentControlWidget, tr("Resident"));
    tabWidget->addTab(householdControlWidget, tr("Household"));
    tabWidget->addTab(chatWidgetForManager, tr("Chat"));
    setCentralWidget(tabWidget);

    connect(residentControlWidget, &ResidentControlWidget::residentAdded, householdControlWidget, &HouseholdControlWidget::onResidentListUpdated);
    connect(residentControlWidget, &ResidentControlWidget::residentDeleted, householdControlWidget, &HouseholdControlWidget::onResidentListUpdated);
    connect(residentControlWidget, &ResidentControlWidget::residentAdded, chatWidgetForManager, &ChatWidgetForManager::onResidentListUpdated);
    connect(residentControlWidget, &ResidentControlWidget::residentDeleted, chatWidgetForManager, &ChatWidgetForManager::onResidentListUpdated);

}

void MainWindow::setupTabsForResident(Resident *resident){
    QTabWidget *tabWidget = new QTabWidget(this);

    residentHomeWidget = new ResidentHomeWidget(resident, residentManager, householdManager, this);
    sensorControlWidget = new SensorControlWidget(resident, residentManager, householdManager, this);
    chatWidgetForResident = new ChatWidgetForResident(resident, managerManager, residentManager, householdManager, this);

    tabWidget->addTab(residentHomeWidget, tr("Home"));
    tabWidget->addTab(sensorControlWidget, tr("Control"));
    tabWidget->addTab(chatWidgetForResident, tr("Chat"));
    setCentralWidget(tabWidget);


}

