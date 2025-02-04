#include "department.h"

Department::Department(const std::string& name) : _name(name) {}

Department::Department() : _name("") {}

void Department::addPatient(int patientId, int priority) {
    QueueEntry entry{patientId, priority, std::time(nullptr)};
    _priorityQueue.push(entry);
    _patientIndex[patientId] = entry;
}

void Department::removePatient(int patientId) {
    // Note: In practice, you'd need to rebuild the priority queue
    // This is a simplified version
    _patientIndex.erase(patientId);
}

std::vector<Department::QueueEntry> Department::getQueue() const {
    std::vector<QueueEntry> queue;
    for (const auto& [id, entry] : _patientIndex) {
        queue.push_back(entry);
    }
    return queue;
}