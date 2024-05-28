#include "Login.h"
#include <QMessageBox>

Login::Login(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    setWindowIcon(QIcon("plus.ico"));
}

Login::~Login()
{}

void Login::on_pushButton_login_clicked()
{
    QString username = ui.lineEdit_username->text();
    QString password = ui.lineEdit_password->text();

    if (username == "admin" && password == "admin") {
        accept(); // Akceptacja logowania
    }
    else {
        QMessageBox::warning(this, "Logowanie nie powiodlo sie", "Zly login lub haslo");
    }
}

void Login::on_pushButton_login_2_clicked()
{
    reject(); // Anulowanie logowania
}
