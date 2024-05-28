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
    void on_pushButtonLogin_clicked();
    void on_pushButtonLogin2_clicked();

private:
    Ui::LoginClass ui;
};
