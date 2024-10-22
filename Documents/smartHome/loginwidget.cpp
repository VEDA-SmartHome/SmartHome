#include "loginwidget.h"
#include <QDebug>

LoginWidget::LoginWidget(Login* loginController, QWidget *parent) :
    QWidget(parent), ui(new Ui::LoginWidget), loginController(loginController)
{
    ui->setupUi(this);


    QLabel* logoLabel = findChild<QLabel*>("logoImg");
    QPixmap pixmap(":/logoImage/images/HOME.png");
    logoLabel->setPixmap(pixmap);


    userTypeComboBox = findChild<QComboBox*>("comboBox");
    idEdit = findChild<QLineEdit*>("idEdit");
    pwEdit = findChild<QLineEdit*>("pwEdit");
    loginButton = findChild<QPushButton*>("pushButton");
    connect(loginButton, &QPushButton::clicked, this, &LoginWidget::loginButtonClicked);
}

LoginWidget::~LoginWidget(){
    delete ui;
}

void LoginWidget::loginButtonClicked(){
    QString userType = userTypeComboBox->currentText();
    QString id = idEdit->text();
    QString pw = pwEdit->text();

    if(userType == "manager"){
        Manager* manager = loginController->authenticateManager(id, pw);
        if(manager != nullptr){
            emit managerLoginSuccess(manager);
        }else{
            qDebug() << "Manager login failed";
        }
    }else if(userType == "resident"){
        Resident* resident = loginController->authenticateResident(id, pw);
        if(resident != nullptr){
            emit residentLoginSuccess(resident);
        }else{
            qDebug() << "Resident login failed";
        }
    }
}
