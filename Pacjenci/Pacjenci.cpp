#include "Pacjenci.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QtPatientInput.h>
#include <PatientClass.h>
/*
Pacjenci::Pacjenci(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowIcon(QIcon("plus.ico"));
    //ReadData_ButtonClicked();
    //ui.patientTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
*/
/*
Pacjenci::Pacjenci(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);
    setWindowIcon(QIcon("plus.ico"));

    // Stw�rz centralny widget, kt�ry b�dzie trzyma� layout
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Dodaj patientTable do mainLayout
    mainLayout->addWidget(ui.patientTable);

    // Ustaw centralWidget w QMainWindow
    setCentralWidget(centralWidget);

    // Ustawienie polityki rozmiaru dla tabeli, aby elastycznie skalowa�a si� wraz z oknem
    ui.patientTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    //buttonLayout->addWidget(ui.patientTable);
    buttonLayout->addWidget(ui.ButtonDelete);
    buttonLayout->addWidget(ui.ButtonAdd);
    buttonLayout->addWidget(ui.ReadDataButton);
    buttonLayout->addWidget(ui.SendDataButton);
    mainLayout->addLayout(buttonLayout);
}
*/

#include "Pacjenci.h"

Pacjenci::Pacjenci(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);
    setWindowIcon(QIcon("plus.ico"));

    // Stworzenie centralnego widgetu, kt�ry b�dzie trzyma� g��wny uk�ad (layout)
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Dodanie patientTable do g��wnego uk�adu i ustawienie polityki rozmiaru
    ui.patientTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(ui.patientTable);

    // Dodanie elastyczno�ci (stretch) przed przyciskami, aby umiejscowi� przyciski w centrum
    mainLayout->addStretch(1);

    // Stworzenie poziomego uk�adu dla przycisk�w
    QHBoxLayout* buttonLayout = new QHBoxLayout;

    // Ustawienie polityki rozmiaru dla przycisk�w, aby unikn�� ich niew�a�ciwego rozci�gania
    QSizePolicy buttonPolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    ui.ButtonDelete->setSizePolicy(buttonPolicy);
    ui.ButtonAdd->setSizePolicy(buttonPolicy);
    ui.ReadDataButton->setSizePolicy(buttonPolicy);
    ui.SendDataButton->setSizePolicy(buttonPolicy);

    // Dodanie przycisk�w do poziomego uk�adu
    buttonLayout->addWidget(ui.ButtonDelete);
    buttonLayout->addWidget(ui.ButtonAdd);
    buttonLayout->addWidget(ui.ReadDataButton);
    buttonLayout->addWidget(ui.SendDataButton);

    // Dodanie poziomego uk�adu z przyciskami do g��wnego uk�adu
    mainLayout->addLayout(buttonLayout);

    // Dodanie elastyczno�ci (stretch) po przyciskach, aby przyciski pozosta�y wycentrowane
    mainLayout->addStretch(1);

    // Ustawienie centralnego widgetu QMainWindow
    setCentralWidget(centralWidget);

    QHeaderView* header = ui.patientTable->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

}


Pacjenci::~Pacjenci()
{
    //saveItemsToFile(ui.patientTable, "output.txt");
}

void Pacjenci::DeletePatientButtonClicked()
{
    int currentRow = ui.patientTable->currentRow(); // Pobierz indeks aktualnie zaznaczonego rz�du

    if (currentRow != -1) { // Sprawd�, czy rzeczywi�cie jaki� rz�d jest zaznaczony
        // Usu� zaznaczony rz�d z tabeli
        ui.patientTable->removeRow(currentRow);

        // Usu� odpowiadaj�cy mu obiekt pacjenta z wektora
        if (currentRow < patients.size()) { // Dodatkowe zabezpieczenie
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

    /* //Dodawanie do widgetlist
    QString str = ui.lineEdit->text();
    QListWidgetItem* item = new QListWidgetItem(str);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui.lista_pacjentow->addItem(item);

    //QString str = ui.lineEdit->text();
    //ui.lista_pacjentow->addItem(str);


    //ui.lista_pacjentow->item
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon("plus.ico"));
    msgBox.setText("Pomyslnie dodano pacjenta");
    msgBox.setWindowTitle("Komunikat ");
    msgBox.exec();
    ui.lineEdit->clear();
    */
     // Dodawanie do tablewidget
    
   

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

    // Sprawdzenie, czy PESEL ma dok�adnie 11 cyfr
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

    // Sprawdzenie poprawno�ci miesi�ca
    int month = str3.mid(2, 2).toInt();
    if (!((month >= 1 && month <= 12) || (month >= 21 && month <= 32))) {
        QMessageBox::warning(this, "B\u0142\u0105d", "Miesi\u0105c w PESEL-u musi mie\u015bci\u0107 si\u0119 w przedziale 01-12 lub 21-32!");
        return;
    }

    // Sprawdzenie poprawno\u015bci dnia
    int day = str3.mid(4, 2).toInt();
    if (day < 1 || day > 31) {
        QMessageBox::warning(this, "B\u0142\u0105d", "Dzie\u0144 w PESEL-u musi mie\u015bci\u0107 si\u0119 w przedziale 01-31!");
        return;
    }

    // Obliczenie cyfry kontrolnej
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
    /*
    int row = ui.patientTable->rowCount(); // Pobierz aktualn� liczb� wierszy
    ui.patientTable->insertRow(row); // Dodaj nowy wiersz na ko�cu

    QTableWidgetItem* newItem = new QTableWidgetItem(str);
    ui.patientTable->setItem(row, 0, newItem); // Dodaj element do pierwszej kolumny nowego wiersza
    
    QTableWidgetItem* newItem1 = new QTableWidgetItem(str1);
    ui.patientTable->setItem(row, 1, newItem1);

    QTableWidgetItem* newItem2 = new QTableWidgetItem(str2);
    ui.patientTable->setItem(row, 2, newItem2);

    QTableWidgetItem* newItem3 = new QTableWidgetItem(str3);
    ui.patientTable->setItem(row, 3, newItem3);

    QTableWidgetItem* newItem4 = new QTableWidgetItem(str4);
    ui.patientTable->setItem(row, 4, newItem4);
    */
    QMessageBox::information(this, "Komunikat", "Pomyslnie dodano pacjenta");
    
    isAddingNewPatient = false;
}

void Pacjenci::ItemChanged() 
{
    if (isAddingNewPatient) {
        return; // Je�li jeste�my w trakcie dodawania pacjenta, nie robimy nic
    }

    QTableWidgetItem* item = ui.patientTable->currentItem();
    if (!item) return; // Je�li nie ma zaznaczonego elementu, nic nie r�b

    int row = item->row();
    int column = item->column();

    if (row >= 0 && row < patients.size()) {
        PatientClass& patient = patients[row];

        // Zaktualizuj obiekt pacjenta na podstawie zmodyfikowanej kom�rki
        switch (column) {
        case 0: // Imi�
            patient.setName(item->text());
            break;
        case 1: // Nazwisko
            patient.setSurname(item->text());
            break;
        case 2: // Wiek
            patient.setAge(item->text().toInt());
            break;
        case 3: // PESEL
            patient.setPesel(item->text());
            break;
        case 4: // Koszt leczenia
            patient.setTreatmentCost(item->text());
            break;
        case 5: // Ubezpieczony
            patient.setInsured(item->text() == "Tak");
            break;
        case 6: // Status leczenia
            patient.setTreatmentStatus(item->text());
            break;
        }

        QMessageBox::information(this, "Komunikat", "Edytowano pacjenta");

    }
    else {
        // Obs�uga b��du - wiersz poza zakresem
        QMessageBox::warning(this, "B\u0142\u0105d", "Niepoprawne dane pacjenta.");
    }
}



void Pacjenci::SaveToFileButtonClicked()
{
    SaveItemsToFile(ui.patientTable, "output.txt"); // Zapisz elementy do pliku

    QMessageBox::information(this, "Komunikat", "Pomyslnie skopiowano do pliku");

   /* QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon("plus.ico"));
    msgBox.setText("Pomyslnie skopiowano do pliku");
    msgBox.setWindowTitle("Komunikat");
    msgBox.setStyleSheet("QMessageBox { background-image: url(:/Pacjenci/tlo.png); }");
    msgBox.exec();*/
}


void Pacjenci::SaveItemsToFile(QTableWidget* listWidget, const QString& fileName) {

      // Nazwa pliku do zapisu
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "B\u0142\u0105d", "Nie mo\u017cna otworzy\u0107 pliku do zapisu.");
        return;
    }

    QTextStream out(&file);

    // Iteracja przez wiersze i kolumny tabeli
    for (int row = 0; row < ui.patientTable->rowCount(); ++row) {
        QStringList rowData;  // Lista na dane z jednego wiersza
        for (int column = 0; column < ui.patientTable->columnCount(); ++column) {
            QTableWidgetItem* item = ui.patientTable->item(row, column);
            rowData << (item ? item->text() : "");  // Dodaj tekst kom�rki lub pusty string
        }
        out << rowData.join(",") << "\n";  // Po��cz dane z wiersza i zapisz jako jedn� lini�
    }

    file.close();  // Zamknij plik
    //QMessageBox::information(this, "Informacja", "Dane zosta�y zapisane do pliku 'output.txt'.");

    /*
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return; // Nie uda�o si� otworzy� pliku, obs�uga b��du

    QTextStream out(&file);
    for (int i = 0; i < listWidget->count(); ++i) {
        QListWidgetItem* item = listWidget->item(i);
        if (item) {
            out << item->text() << "\n"; // Zapisz tekst elementu do pliku
        }
    }

    file.close(); // Pami�taj o zamkni�ciu pliku
    */
}

void Pacjenci::ReadDataButtonClicked()
{
    isAddingNewPatient = true;
    QFile file("output.txt");  // Nazwa pliku z kt�rego b�d� czytane dane
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "B��d", "Nie mo�na otworzy� pliku do odczytu.");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");  // Rozdziel lini� na poszczeg�lne elementy

        if (fields.size() == ui.patientTable->columnCount()) {
            PatientClass newPatient(
                fields[0].trimmed(), // name
                fields[1].trimmed(), // surname
                fields[2].trimmed().toInt(), // age
                fields[3].trimmed(), // pesel
                fields[4].trimmed(), // treatmentCost
                fields[5].trimmed().toLower() == "tak", // insured
                fields[6].trimmed() // treatmentStatus
            );

            patients.append(newPatient);  // Dodaj nowego pacjenta do wektora

            int newRow = ui.patientTable->rowCount();
            ui.patientTable->insertRow(newRow);  // Dodaj nowy wiersz do tabeli

            for (int column = 0; column < fields.size(); ++column) {
                QTableWidgetItem* newItem = new QTableWidgetItem(fields[column].trimmed());
                ui.patientTable->setItem(newRow, column, newItem);  // Ustaw elementy w odpowiednich kolumnach
            }
        }
    }

    file.close();  // Zamknij plik
    isAddingNewPatient = false;
    QMessageBox::information(this, "Informacja", "Dane zosta�y wczytane z pliku.");
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
