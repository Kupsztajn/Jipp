#include "Pacjenci.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pacjenci w;
    w.show();
    return a.exec();
}
