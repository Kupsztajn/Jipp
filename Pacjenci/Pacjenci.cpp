#include "Pacjenci.h"
#include <qmessagebox.h>
Pacjenci::Pacjenci(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

Pacjenci::~Pacjenci()
{}

void Pacjenci::UsunPacjentaButton_clicked()
{
    //ui.lista_pacjentow->takeItem(cur);

    QMessageBox msgBox;
    msgBox.setText("Pomyslnie usunieto pacjenta");
    msgBox.setWindowTitle("Komunikat ");
    msgBox.exec();
}

void Pacjenci::DodajPacjentaButton_clicked()
{
    QString str = ui.lineEdit->text();
    
    ui.lista_pacjentow->addItem(str);
    //ui.lista_pacjentow->item
    QMessageBox msgBox;
    msgBox.setText("Pomyslnie dodano pacjenta");
    msgBox.setWindowTitle("Komunikat ");
    msgBox.exec();
    ui.lineEdit->clear();
}