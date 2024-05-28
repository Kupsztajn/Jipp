#include "Pacjenci.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QtPatientInput.h>
#include <PatientClass.h>

Pacjenci::Pacjenci(QWidget *parent)
    : QMainWindow(parent)

{
    ui.setupUi(this);
    setWindowIcon(QIcon("plus.ico"));
  
   

    //ReadData_ButtonClicked();
    //ui.patientTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


}

/*
Pacjenci::Pacjenci(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);
    setWindowIcon(QIcon("plus.ico"));

    // Stwórz centralny widget, który bêdzie trzyma³ layout
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Dodaj patientTable do mainLayout
    mainLayout->addWidget(ui.patientTable);

    // Ustaw centralWidget w QMainWindow
    setCentralWidget(centralWidget);

    // Ustawienie polityki rozmiaru dla tabeli, aby elastycznie skalowa³a siê wraz z oknem
    ui.patientTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(ui.deleteButton);
    buttonLayout->addWidget(ui.addButton);
    buttonLayout->addWidget(ui.ReadDataButton);
    buttonLayout->addWidget(ui.SendDataButton);
    mainLayout->addLayout(buttonLayout);
}
*/

Pacjenci::~Pacjenci()
{
    //saveItemsToFile(ui.patientTable, "output.txt");
}

void Pacjenci::UsunPacjentaButton_clicked()
{
    int currentRow = ui.patientTable->currentRow(); // Pobierz indeks aktualnie zaznaczonego rzêdu

    if (currentRow != -1) { // SprawdŸ, czy rzeczywiœcie jakiœ rz¹d jest zaznaczony
        // Usuñ zaznaczony rz¹d z tabeli
        ui.patientTable->removeRow(currentRow);

        // Usuñ odpowiadaj¹cy mu obiekt pacjenta z wektora
        if (currentRow < patients.size()) { // Dodatkowe zabezpieczenie
            patients.removeAt(currentRow);
        }

        QMessageBox::information(this, tr("Informacja"), tr("Pomy\u015blnie usuni\u0119to pacjenta"));
    }
    else {
        QMessageBox::warning(this, tr("B\u0142\u0105d"), tr("Nie zaznaczono \u017cadnego pacjenta do usuni\u0119cia"));
    }
}


void Pacjenci::DodajPacjentaButton_clicked()
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

    // Sprawdzenie, czy PESEL ma dok³adnie 11 cyfr
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

    // Sprawdzenie poprawnoœci miesi¹ca
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
    int row = ui.patientTable->rowCount(); // Pobierz aktualn¹ liczbê wierszy
    ui.patientTable->insertRow(row); // Dodaj nowy wiersz na koñcu

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

void Pacjenci::WidgetList_rowChanged(int CurrentRow)
{
    mnSelected = CurrentRow;
}

void Pacjenci::item_changed() {
    if (isAddingNewPatient) {
        return; // Jeœli jesteœmy w trakcie dodawania pacjenta, nie robimy nic
    }

    QTableWidgetItem* item = ui.patientTable->currentItem();
    if (!item) return; // Jeœli nie ma zaznaczonego elementu, nic nie rób

    int row = item->row();
    int column = item->column();

    if (row >= 0 && row < patients.size()) {
        PatientClass& patient = patients[row];

        // Zaktualizuj obiekt pacjenta na podstawie zmodyfikowanej komórki
        switch (column) {
        case 0: // Imiê
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
        // Obs³uga b³êdu - wiersz poza zakresem
        QMessageBox::warning(this, "B\u0142\u0105d", "Niepoprawne dane pacjenta.");
    }
}



void Pacjenci::saveToFile_ButtonClicked()
{
    saveItemsToFile(ui.patientTable, "output.txt"); // Zapisz elementy do pliku

    QMessageBox::information(this, "Komunikat", "Pomyslnie skopiowano do pliku");

   /* QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon("plus.ico"));
    msgBox.setText("Pomyslnie skopiowano do pliku");
    msgBox.setWindowTitle("Komunikat");
    msgBox.setStyleSheet("QMessageBox { background-image: url(:/Pacjenci/tlo.png); }");
    msgBox.exec();*/
}


void Pacjenci::saveItemsToFile(QTableWidget* listWidget, const QString& fileName) {

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
            rowData << (item ? item->text() : "");  // Dodaj tekst komórki lub pusty string
        }
        out << rowData.join(",") << "\n";  // Po³¹cz dane z wiersza i zapisz jako jedn¹ liniê
    }

    file.close();  // Zamknij plik
    //QMessageBox::information(this, "Informacja", "Dane zosta³y zapisane do pliku 'output.txt'.");

    /*
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return; // Nie uda³o siê otworzyæ pliku, obs³uga b³êdu

    QTextStream out(&file);
    for (int i = 0; i < listWidget->count(); ++i) {
        QListWidgetItem* item = listWidget->item(i);
        if (item) {
            out << item->text() << "\n"; // Zapisz tekst elementu do pliku
        }
    }

    file.close(); // Pamiêtaj o zamkniêciu pliku
    */
}

void Pacjenci::ReadData_ButtonClicked()
{
    isAddingNewPatient = true;
    QFile file("output.txt");  // Nazwa pliku z którego bêd¹ czytane dane
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "B³¹d", "Nie mo¿na otworzyæ pliku do odczytu.");
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");  // Rozdziel liniê na poszczególne elementy

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
    QMessageBox::information(this, "Informacja", "Dane zosta³y wczytane z pliku.");
}


void Pacjenci::addPatient(const PatientClass& newPatient) {
    patients.append(newPatient);
    updateTableWidget();
}

void Pacjenci::removePatient(int index) {
    if (index >= 0 && index < patients.size()) {
        patients.removeAt(index);
        updateTableWidget();
    }
}

void Pacjenci::updateTableWidget() {
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
