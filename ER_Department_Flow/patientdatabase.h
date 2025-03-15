#ifndef PATIENTDATABASE_H
#define PATIENTDATABASE_H

#include <map>
#include "patient.h"

class PatientDatabase {
public:
    static PatientDatabase& instance();

    // Generates a unique Patient ID
    int generatePatientId();

    // Stores or updates a Patient object
    void storePatient(const Patient& patient);

    // Finds a Patient by ID
    Patient* findPatient(int patientId);

    void removePatient(int patientId);

private:
    PatientDatabase();

    // Map of patient ID -> Patient
    std::map<int, Patient> _patients;

    // Tracks the last assigned patient ID
    int _lastPatientId;
};

#endif
