// PatientClass.h
#ifndef PATIENTCLASS_H
#define PATIENTCLASS_H

#include <QString>

class PatientClass {
public:
    PatientClass(const QString& name, const QString& surname, int age, const QString& pesel, const QString& treatmentCost, bool isInsured, const QString& treatmentStatus);

    QString getName() const;
    QString getSurname() const;
    int getAge() const;
    QString getPesel() const;
    QString getTreatmentCost() const;
    bool isInsured() const;
    QString getTreatmentStatus() const;

    void setName(const QString& name);
    void setSurname(const QString& surname);
    void setAge(int age);
    void setPesel(const QString& pesel);
    void setTreatmentCost(const QString& cost);
    void setInsured(bool insured);
    void setTreatmentStatus(const QString& status);

private:
    QString name;
    QString surname;
    int age;
    QString pesel;
    QString treatmentCost;
    bool insured;
    QString treatmentStatus;
};

#endif // PATIENTCLASS_H
