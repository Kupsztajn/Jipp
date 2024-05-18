#include "QtPatientInput.h"
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

QtPatientInput::QtPatientInput(QWidget* parent) : QDialog(parent) {
    inputName = new QLineEdit(this);
    inputSurname = new QLineEdit(this);
    inputAge = new QLineEdit(this);
    inputPesel = new QLineEdit(this);
    inputTreatmentCost = new QLineEdit(this);

    acceptButton = new QPushButton("Accept", this);
    cancelButton = new QPushButton("Cancel", this);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow("Name", inputName);
    formLayout->addRow("Surname", inputSurname);
    formLayout->addRow("Age", inputAge);
    formLayout->addRow("Pesel", inputPesel);
    formLayout->addRow("Treatment Cost", inputTreatmentCost);
    mainLayout->addLayout(formLayout);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(acceptButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);

    connect(acceptButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString QtPatientInput::getName() const { return inputName->text(); }
QString QtPatientInput::getSurname() const { return inputSurname->text(); }
QString QtPatientInput::getAge() const { return inputAge->text(); }
QString QtPatientInput::getPesel() const { return inputPesel->text(); }
QString QtPatientInput::getTreatmentCost() const { return inputTreatmentCost->text(); }
