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
    void OnPushButtonLoginClicked();
    void OnPushButtonLogin2Clicked();

private:
    Ui::LoginClass ui;
};
