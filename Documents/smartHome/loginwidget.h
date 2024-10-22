#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include "ui_loginwidget.h"
#include "login.h"

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(Login* loginController, QWidget *parent = nullptr);
    ~LoginWidget();

private slots:
    void loginButtonClicked();

signals:
    void managerLoginSuccess(Manager* manager);
    void residentLoginSuccess(Resident* resident);

private:
    Ui::LoginWidget *ui;
    QComboBox *userTypeComboBox;
    QLineEdit *idEdit;
    QLineEdit *pwEdit;
    QPushButton *loginButton;
    Login *loginController;
};

#endif // LOGINWIDGET_H
