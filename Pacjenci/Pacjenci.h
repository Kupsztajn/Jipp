#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Pacjenci.h"
#include <QVector>
#include "PatientClass.h"

class Pacjenci : public QMainWindow
{
    Q_OBJECT

public:
    Pacjenci(QWidget *parent = nullptr);
    ~Pacjenci();

private:
    Ui::PacjenciClass ui;
    int mnSelected = -1;
    bool isAddingNewPatient = false;
    QVector<PatientClass> patients;

    private slots:
        void DodajPacjentaButton_clicked();
        void UsunPacjentaButton_clicked();
        void WidgetList_rowChanged(int CurrentRow);
        void item_changed();
        void saveToFile_ButtonClicked();
        void saveItemsToFile(QTableWidget* listWidget, const QString& fileName); // do usuniecia
        void ReadData_ButtonClicked();
        void addPatient(const PatientClass& newPatient);
        void removePatient(int index);
        void updateTableWidget();
};
