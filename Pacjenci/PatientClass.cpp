// PatientClass.cpp
#include "PatientClass.h"

PatientClass::PatientClass(const QString& name, const QString& surname, int age, const QString& pesel, const QString& treatmentCost, bool isInsured, const QString& treatmentStatus)
    : name(name), surname(surname), age(age), pesel(pesel), treatmentCost(treatmentCost), insured(isInsured), treatmentStatus(treatmentStatus) {}

QString PatientClass::getName() const { return name; }
QString PatientClass::getSurname() const { return surname; }
int PatientClass::getAge() const { return age; }
QString PatientClass::getPesel() const { return pesel; }
QString PatientClass::getTreatmentCost() const { return treatmentCost; }
bool PatientClass::isInsured() const { return insured; }
QString PatientClass::getTreatmentStatus() const { return treatmentStatus; }
