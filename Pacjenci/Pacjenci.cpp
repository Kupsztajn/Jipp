#include "Pacjenci.h"
#include <qmessagebox.h>
Pacjenci::Pacjenci(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.lista_pacjentow->addItem("test");
}

Pacjenci::~Pacjenci()
{}

void Pacjenci::UsunPacjentaButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("Pomyslnie usunieto pacjenta");
    msgBox.setWindowTitle("Komunikat ");
    msgBox.exec();
}

void Pacjenci::DodajPacjentaButton_clicked()
{
    ui.lista_pacjentow->addItem("Test dodaj");
    //ui.lista_pacjentow->item
    QMessageBox msgBox;
    msgBox.setText("Pomyslnie dodano pacjenta");
    msgBox.setWindowTitle("Komunikat ");
    msgBox.exec();
}