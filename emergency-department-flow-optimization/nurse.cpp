#include "nurse.h"

Nurse::Nurse(int nurseId, std::string name)
    : _nurseId(nurseId)
    , _name(std::move(name))
{}

Nurse::Nurse()
    : _nurseId(0)
    , _name("")
{}