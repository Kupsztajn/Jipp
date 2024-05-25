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
    //ui.tabela_pacjentow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


}

/*
Pacjenci::Pacjenci(QWidget* parent) : QMainWindow(parent) {
    ui.setupUi(this);
    setWindowIcon(QIcon("plus.ico"));

    // Stw�rz centralny widget, kt�ry b�dzie trzyma� layout
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Dodaj tabela_pacjentow do mainLayout
    mainLayout->addWidget(ui.tabela_pacjentow);

    // Ustaw centralWidget w QMainWindow
    setCentralWidget(centralWidget);

    // Ustawienie polityki rozmiaru dla tabeli, aby elastycznie skalowa�a si� wraz z oknem
    ui.tabela_pacjentow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(ui.Button_Usun);
    buttonLayout->addWidget(ui.Button_Dodaj);
    buttonLayout->addWidget(ui.ReadDataButton);
    buttonLayout->addWidget(ui.SendDataButton);
    mainLayout->addLayout(buttonLayout);
}
*/

Pacjenci::~Pacjenci()
{
    //saveItemsToFile(ui.tabela_pacjentow, "output.txt");
}

void Pacjenci::UsunPacjentaButton_clicked() 
{
    int currentRow = ui.tabela_pacjentow->currentRow(); // Pobierz indeks aktualnie zaznaczonego rz�du

    if (currentRow != -1) { // Sprawd�, czy rzeczywi�cie jaki� rz�d jest zaznaczony
        // Usu� zaznaczony rz�d z tabeli
        ui.tabela_pacjentow->removeRow(currentRow);

        // Usu� odpowiadaj�cy mu obiekt pacjenta z wektora
        if (currentRow < patients.size()) { // Dodatkowe zabezpieczenie
            patients.removeAt(currentRow);
        }

        QMessageBox::information(this, tr("Informacja"), tr("Pomy�lnie usuni�to pacjenta"));
    }
    else {
        QMessageBox::warning(this, tr("B��d"), tr("Nie zaznaczono �adnego pacjenta do usuni�cia"));
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

        int row = ui.tabela_pacjentow->rowCount();
        ui.tabela_pacjentow->insertRow(row);
        ui.tabela_pacjentow->setItem(row, 0, new QTableWidgetItem(dialog.getName()));
        ui.tabela_pacjentow->setItem(row, 1, new QTableWidgetItem(dialog.getSurname()));
        ui.tabela_pacjentow->setItem(row, 2, new QTableWidgetItem(dialog.getAge()));
        ui.tabela_pacjentow->setItem(row, 3, new QTableWidgetItem(dialog.getPesel()));
        ui.tabela_pacjentow->setItem(row, 4, new QTableWidgetItem(dialog.getTreatmentCost()));
        ui.tabela_pacjentow->setItem(row, 5, new QTableWidgetItem(dialog.isInsured() ? "Tak" : "Nie"));
        ui.tabela_pacjentow->setItem(row, 6, new QTableWidgetItem(dialog.getTreatmentStatus()));
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
        QMessageBox::warning(this, "B��d", "PESEL musi zawiera� dok�adnie 11 cyfr!");
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
        QMessageBox::warning(this, "B��d", "PESEL musi zawiera� wy��cznie cyfry!");
        return;
    }

    // Sprawdzenie poprawno�ci miesi�ca
    int month = str3.mid(2, 2).toInt();
    if (!((month >= 1 && month <= 12) || (month >= 21 && month <= 32))) {
        QMessageBox::warning(this, "B��d", "Miesi�c w PESEL-u musi mie�ci� si� w przedziale 01-12 lub 21-32!");
        return;
    }

    // Sprawdzenie poprawno�ci dnia
    int day = str3.mid(4, 2).toInt();
    if (day < 1 || day > 31) {
        QMessageBox::warning(this, "B��d", "Dzie� w PESEL-u musi mie�ci� si� w przedziale 01-31!");
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
        QMessageBox::warning(this, "B��d", "Cyfra kontrolna PESELU jest niepoprawna!");
        return;
    }


    QString str4 = dialog.getTreatmentCost();
    if (str4.isEmpty()) {
        QMessageBox::warning(this, "B\u0142\u0105d", "Nie wprowadzono kosztu leczenia pacjenta lub reszty danych!");
        return;
    }
    /*
    int row = ui.tabela_pacjentow->rowCount(); // Pobierz aktualn� liczb� wierszy
    ui.tabela_pacjentow->insertRow(row); // Dodaj nowy wiersz na ko�cu

    QTableWidgetItem* newItem = new QTableWidgetItem(str);
    ui.tabela_pacjentow->setItem(row, 0, newItem); // Dodaj element do pierwszej kolumny nowego wiersza
    
    QTableWidgetItem* newItem1 = new QTableWidgetItem(str1);
    ui.tabela_pacjentow->setItem(row, 1, newItem1);

    QTableWidgetItem* newItem2 = new QTableWidgetItem(str2);
    ui.tabela_pacjentow->setItem(row, 2, newItem2);

    QTableWidgetItem* newItem3 = new QTableWidgetItem(str3);
    ui.tabela_pacjentow->setItem(row, 3, newItem3);

    QTableWidgetItem* newItem4 = new QTableWidgetItem(str4);
    ui.tabela_pacjentow->setItem(row, 4, newItem4);
    */
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon("plus.ico"));
    msgBox.setText("Pomy\u0347lnie dodano pacjenta"); // !!!!
    msgBox.setWindowTitle("Komunikat");
    msgBox.exec();
    
    isAddingNewPatient = false;
}

void Pacjenci::WidgetList_rowChanged(int CurrentRow)
{
    mnSelected = CurrentRow;
}

void Pacjenci::item_changed() {
    if (isAddingNewPatient) {
        return; // Je�li jeste�my w trakcie dodawania pacjenta, nie robimy nic
    }

    QTableWidgetItem* item = ui.tabela_pacjentow->currentItem();
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

        QMessageBox msgBox;
        msgBox.setWindowIcon(QIcon("plus.ico"));
        msgBox.setText("Edytowano pacjenta");
        msgBox.setWindowTitle("Komunikat ");
        msgBox.exec();
    }
    else {
        // Obs�uga b��du - wiersz poza zakresem
        QMessageBox::warning(this, "B��d", "Niepoprawne dane pacjenta.");
    }
}



void Pacjenci::saveToFile_ButtonClicked()
{
    saveItemsToFile(ui.tabela_pacjentow, "output.txt"); // Zapisz elementy do pliku
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon("plus.ico"));
    msgBox.setText("Pomyslnie skopiowano do pliku");
    msgBox.setWindowTitle("Komunikat");
    msgBox.exec();
}


void Pacjenci::saveItemsToFile(QTableWidget* listWidget, const QString& fileName) {

      // Nazwa pliku do zapisu
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "B��d", "Nie mo�na otworzy� pliku do zapisu.");
        return;
    }

    QTextStream out(&file);

    // Iteracja przez wiersze i kolumny tabeli
    for (int row = 0; row < ui.tabela_pacjentow->rowCount(); ++row) {
        QStringList rowData;  // Lista na dane z jednego wiersza
        for (int column = 0; column < ui.tabela_pacjentow->columnCount(); ++column) {
            QTableWidgetItem* item = ui.tabela_pacjentow->item(row, column);
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

void Pacjenci::ReadData_ButtonClicked()
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

        if (fields.size() == ui.tabela_pacjentow->columnCount()) {  // Upewnij si�, �e ka�da linia ma 5 element�w
            int newRow = ui.tabela_pacjentow->rowCount();
            ui.tabela_pacjentow->insertRow(newRow);  // Dodaj nowy wiersz

            for (int column = 0; column < fields.size(); ++column) {
                QTableWidgetItem* newItem = new QTableWidgetItem(fields[column].trimmed());
                ui.tabela_pacjentow->setItem(newRow, column, newItem);  // Ustaw elementy w odpowiednich kolumnach
            }
        }
    }

    file.close();  // Zamknij plik
    QMessageBox::information(this, "Informacja", "Dane zosta\u0142y wczytane z pliku.");
    isAddingNewPatient = false;
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
    ui.tabela_pacjentow->clear();
    for (const auto& patient : patients) {
        int row = ui.tabela_pacjentow->rowCount();
        ui.tabela_pacjentow->insertRow(row);
        ui.tabela_pacjentow->setItem(row, 0, new QTableWidgetItem(patient.getName()));
        ui.tabela_pacjentow->setItem(row, 1, new QTableWidgetItem(patient.getSurname()));
        ui.tabela_pacjentow->setItem(row, 2, new QTableWidgetItem(patient.getAge()));
        ui.tabela_pacjentow->setItem(row, 3, new QTableWidgetItem(patient.getPesel()));
        ui.tabela_pacjentow->setItem(row, 4, new QTableWidgetItem(patient.getTreatmentCost()));
        ui.tabela_pacjentow->setItem(row, 5, new QTableWidgetItem(patient.isInsured() ? "Tak" : "Nie"));
        ui.tabela_pacjentow->setItem(row, 6, new QTableWidgetItem(patient.getTreatmentStatus()));
    }
}
