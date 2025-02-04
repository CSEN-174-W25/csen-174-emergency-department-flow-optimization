#include "patient.h"

Patient::Patient(int patientId, std::string name, std::string gender,
                std::string contact, std::string emergencyContact, std::string addr)
    : _patientId(patientId)
    , _name(std::move(name))
    , _gender(std::move(gender))
    , _contact(std::move(contact))
    , _emergencyContact(std::move(emergencyContact))
    , _homeAddr(std::move(addr))
    , _insuranceProvider("")
    , _insuranceMemberId("")
    , _medicalHistory("")
    , _familyHistory("")
    , _currentMedications("")
    , _allergies("")
{
}

Patient::Patient()
    : _patientId(0)
    , _name("")
    , _gender("")
    , _contact("")
    , _emergencyContact("")
    , _homeAddr("")
    , _insuranceProvider("")
    , _insuranceMemberId("")
    , _medicalHistory("")
    , _familyHistory("")
    , _currentMedications("")
    , _allergies("")
{
}