#include "Pacjenci.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QtPatientInput.h>
#include <PatientClass.h>

Pacjenci::Pacjenci(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);
    setWindowIcon(QIcon("plus.ico"));

    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    ui.patientTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(ui.patientTable);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    QSizePolicy buttonPolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    ui.ButtonDelete->setSizePolicy(buttonPolicy);
    ui.ButtonAdd->setSizePolicy(buttonPolicy);
    ui.ReadDataButton->setSizePolicy(buttonPolicy);
    ui.SendDataButton->setSizePolicy(buttonPolicy);

    buttonLayout->addWidget(ui.ButtonDelete);
    buttonLayout->addWidget(ui.ButtonAdd);
    buttonLayout->addWidget(ui.ReadDataButton);
    buttonLayout->addWidget(ui.SendDataButton);

    mainLayout->addLayout(buttonLayout);

    setCentralWidget(centralWidget);

    QHeaderView* header = ui.patientTable->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
}


Pacjenci::~Pacjenci()
{}

void Pacjenci::DeletePatientButtonClicked()
{
    int currentRow = ui.patientTable->currentRow();

    if (currentRow != -1) 
    {
        ui.patientTable->removeRow(currentRow);

        if (currentRow < patients.size()) 
        {
            patients.removeAt(currentRow);
        }

        QMessageBox::information(this, tr("Informacja"), tr("Pomy\u015blnie usuni\u0119to pacjenta"));
    }
    else {
        QMessageBox::warning(this, tr("B\u0142\u0105d"), tr("Nie zaznaczono \u017cadnego pacjenta do usuni\u0119cia"));
    }
}


void Pacjenci::AddPatientButtonClicked()
{
    isAddingNewPatient = true;


    QtPatientInput dialog(this);
    if (dialog.exec() == QDialog::Accepted) {

        PatientClass newPatient(
            dialog.getName(),
            dialog.getSurname(),
            dialog.getAge().toInt(),
            dialog.getPesel(),
            dialog.getTreatmentCost(),
            dialog.isInsured(),
            dialog.getTreatmentStatus()
        );

        // Dodanie pacjenta do wektora
        patients.append(newPatient);

        int row = ui.patientTable->rowCount();
        ui.patientTable->insertRow(row);
        ui.patientTable->setItem(row, 0, new QTableWidgetItem(dialog.getName()));
        ui.patientTable->setItem(row, 1, new QTableWidgetItem(dialog.getSurname()));
        ui.patientTable->setItem(row, 2, new QTableWidgetItem(dialog.getAge()));
        ui.patientTable->setItem(row, 3, new QTableWidgetItem(dialog.getPesel()));
        ui.patientTable->setItem(row, 4, new QTableWidgetItem(dialog.getTreatmentCost()));
        ui.patientTable->setItem(row, 5, new QTableWidgetItem(dialog.isInsured() ? "Tak" : "Nie"));
        ui.patientTable->setItem(row, 6, new QTableWidgetItem(dialog.getTreatmentStatus()));
    }

    isAddingNewPatient = false;

    QString str = dialog.getName();

    if (str.isEmpty()) {
        QMessageBox::warning(this, "B\u0142\u0105d", "Nie wprowadzono imienia pacjenta lub reszty danych!");
        return;
    }

    QString str1 = dialog.getSurname();
    if (str1.isEmpty()) {
        QMessageBox::warning(this, "B\u0142\u0105d", "Nie wprowadzono nazwiska pacjenta lub reszty danych!");
        return;
    }

    QString str2 = dialog.getAge();
    if (str2.isEmpty()) {
        QMessageBox::warning(this, "B\u0142\u0105d", "Nie wprowadzono wieku pacjenta lub reszty danych!");
        return;
    }

    QString str3 = dialog.getPesel();
    if (str3.isEmpty()) {
        QMessageBox::warning(this, "B\u0142\u0105d", "Nie wprowadzono PESELU pacjenta lub reszty danych!");
        return;
    }

    if (str3.length() != 11) {
        QMessageBox::warning(this, "B\u0142\u0105d", "PESEL musi zawiera\u0107 dok\u0142adnie 11 cyfr!");
        return;
    }

    bool allDigits = true;
    for (QChar c : str3) {
        if (!c.isDigit()) {
            allDigits = false;
            break;
        }
    }

    if (!allDigits) {
        QMessageBox::warning(this, "B\u0142\u0105d", "PESEL musi zawiera\u0107 wy\u0142\u0105cznie cyfry!");
        return;
    }

    int month = str3.mid(2, 2).toInt();
    if (!((month >= 1 && month <= 12) || (month >= 21 && month <= 32))) {
        QMessageBox::warning(this, "B\u0142\u0105d", "Miesi\u0105c w PESEL-u musi mie\u015bci\u0107 si\u0119 w przedziale 01-12 lub 21-32!");
        return;
    }

    int day = str3.mid(4, 2).toInt();
    if (day < 1 || day > 31) {
        QMessageBox::warning(this, "B\u0142\u0105d", "Dzie\u0144 w PESEL-u musi mie\u015bci\u0107 si\u0119 w przedziale 01-31!");
        return;
    }

    QList<int> weights = { 1, 3, 7, 9, 1, 3, 7, 9, 1, 3 };
    int sum = 0;

    for (int i = 0; i < 10; ++i) {
        int digit = str3[i].digitValue();
        sum += (digit * weights[i]) % 10;
    }

    int calculatedControlDigit = (10 - (sum % 10)) % 10;
    int actualControlDigit = str3[10].digitValue();

    if (calculatedControlDigit != actualControlDigit) {
        QMessageBox::warning(this, "B\u0142\u0105d", "Cyfra kontrolna PESELU jest niepoprawna!");
        return;
    }


    QString str4 = dialog.getTreatmentCost();
    if (str4.isEmpty()) {
        QMessageBox::warning(this, "B\u0142\u0105d", "Nie wprowadzono kosztu leczenia pacjenta lub reszty danych!");
        return;
    }

    QMessageBox::information(this, "Komunikat", "Pomyslnie dodano pacjenta");
    
    isAddingNewPatient = false;
}

void Pacjenci::ItemChanged() 
{
    if (isAddingNewPatient) {
        return;
    }

    QTableWidgetItem* item = ui.patientTable->currentItem();
    if (!item) return;

    int row = item->row();
    int column = item->column();

    if (row >= 0 && row < patients.size()) {
        PatientClass& patient = patients[row];

        switch (column) {
        case 0:
            patient.setName(item->text());
            break;
        case 1:
            patient.setSurname(item->text());
            break;
        case 2:
            patient.setAge(item->text().toInt());
            break;
        case 3:
            patient.setPesel(item->text());
            break;
        case 4:
            patient.setTreatmentCost(item->text());
            break;
        case 5:
            patient.setInsured(item->text() == "Tak");
            break;
        case 6:
            patient.setTreatmentStatus(item->text());
            break;
        }

        QMessageBox::information(this, "Komunikat", "Edytowano pacjenta");

    }
}



void Pacjenci::SaveToFileButtonClicked()
{
    SaveItemsToFile(ui.patientTable, "output.txt");

    QMessageBox::information(this, "Komunikat", "Pomyslnie skopiowano do pliku");
}


void Pacjenci::SaveItemsToFile(QTableWidget* listWidget, const QString& fileName) 
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "B\u0142\u0105d", "Nie mo\u017cna otworzy\u0107 pliku do zapisu.");
        return;
    }

    QTextStream out(&file);

    for (int row = 0; row < ui.patientTable->rowCount(); ++row) {
        QStringList rowData;
        for (int column = 0; column < ui.patientTable->columnCount(); ++column) {
            QTableWidgetItem* item = ui.patientTable->item(row, column);
            rowData << (item ? item->text() : "");
        }
        out << rowData.join(",") << "\n";
    }

    file.close();
}

void Pacjenci::ReadDataButtonClicked()
{
    isAddingNewPatient = true;
    QFile file("output.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "B³¹d", "Nie mo¿na otworzyc pliku do odczytu.");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");

        if (fields.size() == ui.patientTable->columnCount()) {
            PatientClass newPatient(
                fields[0].trimmed(),
                fields[1].trimmed(),
                fields[2].trimmed().toInt(),
                fields[3].trimmed(),
                fields[4].trimmed(),
                fields[5].trimmed().toLower() == "tak",
                fields[6].trimmed()
            );

            patients.append(newPatient);

            int newRow = ui.patientTable->rowCount();
            ui.patientTable->insertRow(newRow);

            for (int column = 0; column < fields.size(); ++column) {
                QTableWidgetItem* newItem = new QTableWidgetItem(fields[column].trimmed());
                ui.patientTable->setItem(newRow, column, newItem);
            }
        }
    }

    file.close();
    isAddingNewPatient = false;
    QMessageBox::information(this, "Informacja", "Dane zosta\u0142y wczytane z pliku.");
}


void Pacjenci::AddPatient(const PatientClass& newPatient) {
    patients.append(newPatient);
    UpdateTableWidget();
}

void Pacjenci::RemovePatient(int index) {
    if (index >= 0 && index < patients.size()) {
        patients.removeAt(index);
        UpdateTableWidget();
    }
}

void Pacjenci::UpdateTableWidget() {
    ui.patientTable->clear();
    for (const auto& patient : patients) {
        int row = ui.patientTable->rowCount();
        ui.patientTable->insertRow(row);
        ui.patientTable->setItem(row, 0, new QTableWidgetItem(patient.getName()));
        ui.patientTable->setItem(row, 1, new QTableWidgetItem(patient.getSurname()));
        ui.patientTable->setItem(row, 2, new QTableWidgetItem(patient.getAge()));
        ui.patientTable->setItem(row, 3, new QTableWidgetItem(patient.getPesel()));
        ui.patientTable->setItem(row, 4, new QTableWidgetItem(patient.getTreatmentCost()));
        ui.patientTable->setItem(row, 5, new QTableWidgetItem(patient.isInsured() ? "Tak" : "Nie"));
        ui.patientTable->setItem(row, 6, new QTableWidgetItem(patient.getTreatmentStatus()));
    }
}
