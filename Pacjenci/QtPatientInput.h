#ifndef QTPATIENTINPUT_H
#define QTPATIENTINPUT_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class QtPatientInput : public QDialog {
    Q_OBJECT

public:
    explicit QtPatientInput(QWidget* parent = nullptr);

    QString getName() const;
    QString getSurname() const;
    QString getAge() const;
    QString getPesel() const;
    QString getTreatmentCost() const;

private:
    QLineEdit* inputName;
    QLineEdit* inputSurname;
    QLineEdit* inputAge;
    QLineEdit* inputPesel;
    QLineEdit* inputTreatmentCost;

    QPushButton* acceptButton;
    QPushButton* cancelButton;
};

#endif // QTPATIENTINPUT_H
