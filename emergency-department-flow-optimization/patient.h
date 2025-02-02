#ifndef PATIENT_H
#define PATIENT_H

#include "main.h"

typedef std::string string;

class patient
{
    public:
        patient(int patientID, string name, string gender, string contact, string emergencyContact, string addr);
        patient();

        //Accessors
        int patientID() {return _patientID;}
        string name() {return _name;}
        string gender() {return _gender;}

        string contact() {return _contact;}
        string emergencyContact() {return _emergencyContact;}
        string homeAddr() {return _homeAddr;}

        //Mutators
        void setPatientID(int id) {_patientID = id;}
        void setName(string name) {_name = name;}
        void setGender(string gender) {_gender = gender;}

        void setContact(string phone) {_contact = phone;}
        void setEmergencyContact(string phone) {_emergencyContact = phone;}
        void setHomeAddr(string addr) {_homeAddr = addr;}


    private:
        int _patientID;

        string _name;
        string _gender;
        QDate _dob;

        string _contact;
        string _emergencyContact;
        string _homeAddr;

        Symptoms _symptoms;

};
#endif // PATIENT_H
