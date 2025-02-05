#include "department.h"

Department::Department(const std::string& name) : _name(name) {}

Department::Department() : _name("") {}

void Department::addPatient(int patientId, int priority) {
    QueueEntry entry{patientId, priority, std::time(nullptr)};
    _priorityQueue.push(entry);
    _patientIndex[patientId] = entry;
}

void Department::removePatient(int patientId) { //Make sure the logic works here
    std::priority_queue<QueueEntry> newPq;
    QueueEntry oldEntry;

    while(!_priorityQueue.empty()){
        oldEntry = _priorityQueue.top();

        if(oldEntry.patientId != patientId)
            newPq.push(oldEntry);
    }
    _patientIndex.erase(patientId);
    _priorityQueue = newPq;
}

void Department::updatePatientPriority(int patientId, int newPriority){ //Make sure the logic works here
    std::priority_queue<QueueEntry> newPq;
    QueueEntry oldEntry, newEntry;

    while(!_priorityQueue.empty()){
        oldEntry = _priorityQueue.top();

        if(oldEntry.patientId != patientId)
            newPq.push(oldEntry);
        else{
            newEntry = oldEntry;
            newEntry.priority = newPriority;
            newPq.push(newEntry);
        }
    }

    _priorityQueue = newPq;
}

std::vector<Department::QueueEntry> Department::getQueue() const {
    std::vector<QueueEntry> queue;
    for (const auto& [id, entry] : _patientIndex) {
        queue.push_back(entry);
    }
    return queue;
}

bool Department::hasPatient(int patientID) const{
    return _patientIndex.find(patientID) != _patientIndex.end();
}

void Department::transferPatient(int patientId, Department& targetDept){

    std::priority_queue<QueueEntry> newPq;
    QueueEntry oldEntry, newEntry;

    while(!_priorityQueue.empty()){
        oldEntry = _priorityQueue.top();

        if(oldEntry.patientId != patientId)
            newPq.push(oldEntry);
        else
            newEntry = oldEntry;
    }

    targetDept._priorityQueue.top()

    _priorityQueue = newPq;
    _patientIndex.erase(patientId);
}
