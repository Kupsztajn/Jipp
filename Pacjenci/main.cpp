#include "Pacjenci.h"
#include "Login.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Login login;
    if (login.exec() == QDialog::Accepted) {
        Pacjenci w;
        w.show();
        return a.exec();
    }
    return 0;
}
