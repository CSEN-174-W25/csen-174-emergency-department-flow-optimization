#include "patient.h"

patient::patient(int patientID, string name, string gender, string contact, string emergencyContact, string addr){
    _patientID = patientID;
    _name = name;
    _gender = gender;
    _contact = contact;
    _emergencyContact = emergencyContact;
    _homeAddr = addr;
}

patient::patient() {}
