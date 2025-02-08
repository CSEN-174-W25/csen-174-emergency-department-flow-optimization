#ifndef PATIENTDATABASE_H
#define PATIENTDATABASE_H

#include <map>
#include "patient.h"

class PatientDatabase {
public:
    // Singleton-like accessor
    static PatientDatabase& instance();

    // Generates a unique Patient ID
    int generatePatientId();

    // Stores or updates a Patient object
    void storePatient(const Patient& patient);

    // Finds a Patient by ID or returns nullptr if not found
    Patient* findPatient(int patientId);

private:
    // Private constructor for singleton usage
    PatientDatabase();

    // Map of patient ID -> Patient
    std::map<int, Patient> _patients;

    // Tracks the last assigned patient ID
    int _lastPatientId;
};

#endif // PATIENTDATABASE_H
