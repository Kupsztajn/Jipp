#include "Pacjenci.h"
#include "Login.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    a.setStyleSheet(
        "QLabel { color: white; }"
        "QLineEdit { color: white; }"
        "QCheckBox { color: white; }"
        "QComboBox { color: black; }"
        "QPushButton { color: white; }"
        "QHeaderView { color: white; }"
        "QComboBox QAbstractItemView { color: white; }"
        );

    // Ustawienie palety kolorów dla aplikacji
    QPalette palette = a.palette();
    palette.setColor(QPalette::WindowText, Qt::white);
    a.setPalette(palette);

    Login login;
    if (login.exec() == QDialog::Accepted) {
        Pacjenci w;
        w.show();
        return a.exec();
    }

    return 0;
}
