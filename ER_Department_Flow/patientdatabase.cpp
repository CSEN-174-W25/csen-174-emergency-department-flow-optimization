#include "patientdatabase.h"

PatientDatabase::PatientDatabase()
    : _lastPatientId(0)
{
    // If needed, you can initialize other fields here.
}

PatientDatabase& PatientDatabase::instance()
{
    static PatientDatabase db;
    return db;
}

int PatientDatabase::generatePatientId()
{
    return ++_lastPatientId;
}

void PatientDatabase::storePatient(const Patient& patient)
{
    _patients[patient.getPatientId()] = patient;
}

Patient* PatientDatabase::findPatient(int patientId)
{
    auto it = _patients.find(patientId);
    if (it != _patients.end()) {
        return &(it->second);
    }
    return nullptr;
}
