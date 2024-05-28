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

void PatientClass::setName(const QString& name) { this->name = name; }
void PatientClass::setSurname(const QString& surname) { this->surname = surname; }
void PatientClass::setAge(int age) { this->age = age; }
void PatientClass::setPesel(const QString& pesel) { this->pesel = pesel; }
void PatientClass::setTreatmentCost(const QString& cost) { this->treatmentCost = cost; }
void PatientClass::setInsured(bool insured) { this->insured = insured; }
void PatientClass::setTreatmentStatus(const QString& status) { this->treatmentStatus = status; }
