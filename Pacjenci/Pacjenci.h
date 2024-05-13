#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Pacjenci.h"

class Pacjenci : public QMainWindow
{
    Q_OBJECT

public:
    Pacjenci(QWidget *parent = nullptr);
    ~Pacjenci();

private:
    Ui::PacjenciClass ui;

    private slots:
        void DodajPacjentaButton_clicked();
};
