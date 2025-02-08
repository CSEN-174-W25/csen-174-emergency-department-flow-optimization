#ifndef PATIENT_H
#define PATIENT_H

#include "main.h"
#include "symptoms.h"
#include <string>
#include <QDate>

class Patient {
public:
    Patient(int patientId, std::string name, std::string gender,
            std::string contact, std::string emergencyContact, std::string addr);
    Patient();

    // Basic info accessors
    int getPatientId() const { return _patientId; }
    std::string getName() const { return _name; }
    std::string getGender() const { return _gender; }
    QDate getDOB() const { return _dob; }
    
    // Contact info accessors
    std::string getContact() const { return _contact; }
    std::string getEmergencyContact() const { return _emergencyContact; }
    std::string getHomeAddr() const { return _homeAddr; }
    
    // Insurance accessors
    std::string getInsuranceProvider() const { return _insuranceProvider; }
    std::string getInsuranceMemberId() const { return _insuranceMemberId; }
    bool hasInsurance() const { return !_insuranceProvider.empty(); }
    
    // Medical history accessors
    std::string getMedicalHistory() const { return _medicalHistory; }
    std::string getFamilyHistory() const { return _familyHistory; }
    std::string getCurrentMedications() const { return _currentMedications; }
    std::string getAllergies() const { return _allergies; }
    
    // Basic info mutators
    void setPatientId(int id) { _patientId = id; }
    void setName(const std::string& name) { _name = name; }
    void setGender(const std::string& gender) { _gender = gender; }
    void setDOB(const QDate& dob) { _dob = dob; }
    
    // Contact info mutators
    void setContact(const std::string& phone) { _contact = phone; }
    void setEmergencyContact(const std::string& phone) { _emergencyContact = phone; }
    void setHomeAddr(const std::string& addr) { _homeAddr = addr; }
    
    // Insurance mutators
    void setInsuranceProvider(const std::string& provider) { _insuranceProvider = provider; }
    void setInsuranceMemberId(const std::string& id) { _insuranceMemberId = id; }
    
    // Medical history mutators
    void setMedicalHistory(const std::string& history) { _medicalHistory = history; }
    void setFamilyHistory(const std::string& history) { _familyHistory = history; }
    void setCurrentMedications(const std::string& medications) { _currentMedications = medications; }
    void setAllergies(const std::string& allergies) { _allergies = allergies; }

    // Get symptoms
    Symptoms& getSymptoms() { return _symptoms; }
    const Symptoms& getSymptoms() const { return _symptoms; }

private:
    int _patientId;
    
    // Basic info
    std::string _name;
    std::string _gender;
    QDate _dob;
    
    // Contact info
    std::string _contact;
    std::string _emergencyContact;
    std::string _homeAddr;
    
    // Insurance info
    std::string _insuranceProvider;
    std::string _insuranceMemberId;
    
    // Medical history
    std::string _medicalHistory;
    std::string _familyHistory;
    std::string _currentMedications;
    std::string _allergies;
    
    // Symptoms
    Symptoms _symptoms;
};
#endif
