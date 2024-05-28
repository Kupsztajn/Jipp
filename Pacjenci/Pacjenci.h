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
        void AddPatientButtonClicked();
        void DeletePatientButtonClicked();
        void WidgetList_rowChanged(int CurrentRow);
        void ItemChanged();
        void SaveToFileButtonClicked();
        void saveItemsToFile(QTableWidget* listWidget, const QString& fileName); // do usuniecia
        void ReadDataButtonClicked();
        void addPatient(const PatientClass& newPatient);
        void removePatient(int index);
        void updateTableWidget();
};