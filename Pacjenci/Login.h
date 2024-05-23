#pragma once

#include <QDialog>
#include "ui_Login.h"

class Login : public QDialog
{
    Q_OBJECT

public:
    Login(QWidget* parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_login_clicked();
    void on_pushButton_login_2_clicked();

private:
    Ui::LoginClass ui;
};
