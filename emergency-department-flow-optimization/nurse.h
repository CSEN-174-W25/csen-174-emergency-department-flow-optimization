#ifndef NURSE_H
#define NURSE_H

#include "main.h"
#include <string>

class Nurse {
public:
    Nurse(int nurseId, std::string name);
    Nurse();

    // Accessors
    int getNurseId() const { return _nurseId; }
    std::string getName() const { return _name; }

    // Mutators
    void setNurseId(int id) { _nurseId = id; }
    void setName(const std::string& name) { _name = name; }

private:
    int _nurseId;
    std::string _name;
};