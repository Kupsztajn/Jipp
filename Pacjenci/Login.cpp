#include "Login.h"
#include <QMessageBox>

Login::Login(QWidget* parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    setWindowIcon(QIcon("plus.ico"));
    ui.lineEditPassword->setEchoMode(QLineEdit::Password);
}

Login::~Login()
{}

void Login::OnPushButtonLoginClicked()
{
    QString username = ui.lineEditUsername->text();
    QString password = ui.lineEditPassword->text();

    if (username == "admin" && password == "admin") {
        accept();
    }
    else {

        QMessageBox msgBox;
        msgBox.setWindowTitle("Logowanie nie powiodlo si\u0119");
        msgBox.setText("Z\u0142y login lub has\u0142o");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStyleSheet("QMessageBox { background-image: url(:/Pacjenci/tlo.png); }");
        msgBox.exec();
    }
}

void Login::OnPushButtonLogin2Clicked()
{
    reject();
}
