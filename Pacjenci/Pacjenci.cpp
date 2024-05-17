#include "Pacjenci.h"
#include <qmessagebox.h>
#include <QFile>
#include <QTextStream>

Pacjenci::Pacjenci(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowIcon(QIcon("plus.ico"));
}

Pacjenci::~Pacjenci()
{}

void Pacjenci::UsunPacjentaButton_clicked()
{
    int currentRow = ui.tabela_pacjentow->currentRow(); // Pobierz indeks aktualnie zaznaczonego rz�du

    if (currentRow != -1) { // Sprawd�, czy rzeczywi�cie jaki� rz�d jest zaznaczony
        ui.tabela_pacjentow->removeRow(currentRow); // Usu� zaznaczony rz�d

        QMessageBox::information(this, "Informacja", "Pomy�lnie usuni�to pacjenta");
    }
    else {
        QMessageBox::warning(this, "B��d", "Nie zaznaczono �adnego pacjenta do usuni�cia");
    }
}


void Pacjenci::DodajPacjentaButton_clicked()
{
    isAddingNewPatient = true;
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
    QString str = ui.lineEdit->text();
    if (str.isEmpty()) {
        QMessageBox::warning(this, "B��d", "Nie wprowadzono imienia pacjenta!");
        return;
    }

    QString str1 = ui.lineEdit_2->text();
    if (str1.isEmpty()) {
        QMessageBox::warning(this, "B��d", "Nie wprowadzono nazwiska pacjenta!");
        return;
    }

    QString str2 = ui.lineEdit_3->text();
    if (str2.isEmpty()) {
        QMessageBox::warning(this, "B��d", "Nie wprowadzono wieku pacjenta!");
        return;
    }

    QString str3 = ui.lineEdit_4->text();
    if (str3.isEmpty()) {
        QMessageBox::warning(this, "B��d", "Nie wprowadzono PESELU pacjenta!");
        return;
    }

    QString str4 = ui.lineEdit_5->text();
    if (str4.isEmpty()) {
        QMessageBox::warning(this, "B��d", "Nie wprowadzono kosztu leczenia pacjenta!");
        return;
    }

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

    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon("plus.ico"));
    msgBox.setText("Pomy�lnie dodano pacjenta");
    msgBox.setWindowTitle("Komunikat");
    msgBox.exec();

    ui.lineEdit->clear(); // Wyczy�� pole tekstowe
    isAddingNewPatient = false;
}

void Pacjenci::WidgetList_rowChanged(int CurrentRow)
{
    mnSelected = CurrentRow;
}

void Pacjenci::item_changed()
{
    if (isAddingNewPatient) {
        return; // Je�li jeste�my w trakcie dodawania pacjenta, nie robimy nic
    }

    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon("plus.ico"));
    msgBox.setText("Edytowano pacjenta");
    msgBox.setWindowTitle("Komunikat ");
    msgBox.exec();
}

void Pacjenci::saveToFile_ButtonClicked()
{
    saveItemsToFile(ui.lista_pacjentow, "output.txt"); // Zapisz elementy do pliku
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon("plus.ico"));
    msgBox.setText("Pomyslnie skopiowano do pliku");
    msgBox.setWindowTitle("Komunikat");
    msgBox.exec();
}


void Pacjenci::saveItemsToFile(QListWidget* listWidget, const QString& fileName) { // do usuniecia
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
}

void Pacjenci::saveTableToFile() {
    QString fileName = "output.txt";  // Nazwa pliku do zapisu
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
    QMessageBox::information(this, "Informacja", "Dane zosta�y zapisane do pliku 'output.txt'.");
}
