#include "Pacjenci.h"
#include "Login.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    a.setStyleSheet(
        "QLabel { color: red; }"
        "QLineEdit { color: red; }"
        "QCheckBox { color: red; }"
        "QComboBox { color: red; }"
        "QPushButton { color: red; }"
    );

    // Ustawienie palety kolorów dla aplikacji
    QPalette palette = a.palette();
    palette.setColor(QPalette::WindowText, Qt::red);
    a.setPalette(palette);

    Login login;
    if (login.exec() == QDialog::Accepted) {
        Pacjenci w;
        w.show();
        return a.exec();
    }
    return 0;
}
