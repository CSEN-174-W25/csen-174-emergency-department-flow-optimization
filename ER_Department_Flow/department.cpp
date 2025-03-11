#include "department.h"

Department::Department(const std::string& name) : _name(name) {}

Department::Department() : _name("") {}

void Department::addPatient(int patientId, int priority) {
    QueueEntry entry{patientId, priority, std::time(nullptr)};
    _priorityQueue.push(entry);
    _patientIndex[patientId] = entry;
}

void Department::addPatient(int patientId, int priority, std::time_t entryTime) {
    QueueEntry entry{patientId, priority, entryTime};
    _priorityQueue.push(entry);
    _patientIndex[patientId] = entry;
}

void Department::removePatient(int patientId) {
    _patientIndex.erase(patientId);
    // Rebuild the priority queue from the updated _patientIndex.
    std::priority_queue<QueueEntry> newQueue;
    for (const auto& pair : _patientIndex) {
        newQueue.push(pair.second);
    }
    _priorityQueue = std::move(newQueue);
}


std::vector<Department::QueueEntry> Department::getQueue() const {
    std::vector<QueueEntry> queue;
    for (const auto& [id, entry] : _patientIndex) {
        queue.push_back(entry);
    }
    return queue;
}

void Department::updatePatientPriority(int patientId, int newPriority) {
    // Check if the patient exists in the index.
    auto it = _patientIndex.find(patientId);
    if (it != _patientIndex.end()) {
        // Retrieve the current entry.
        QueueEntry entry = it->second;

        // Preserve the original entry time instead of resetting it
        std::time_t originalEntryTime = entry.entryTime;

        // Update the entry with the new priority but keep the original entry time
        entry.priority = newPriority;
        entry.entryTime = originalEntryTime; // Keep original time instead of using std::time(nullptr)

        // Remove the old entry from the index.
        _patientIndex.erase(it);

        // Insert the updated entry into the priority queue.
        _priorityQueue.push(entry);

        // Update the index with the new entry.
        _patientIndex[patientId] = entry;
    }
}

std::string Department::getName() const {
    return _name;
}

void Department::transferPatient(int patientId, Department& targetDept) {
    // Look for the patient in the current department's index.
    auto it = _patientIndex.find(patientId);
    if (it != _patientIndex.end()) {
        // Retrieve the current priority from the entry.
        int priority = it->second.priority;
        std::time_t entryTime = it->second.entryTime;

        // Remove the patient from the current department.
        // Note: Removing from the _priorityQueue directly is non-trivial,
        // so in a simple implementation we just remove from _patientIndex.
        _patientIndex.erase(it);

        // Optionally, you could rebuild the entire _priorityQueue here,
        // or simply allow the stale entry to remain if it won’t affect behavior.

        // Add the patient to the target department with the same priority.
        targetDept.addPatient(patientId, priority, entryTime);
    }
}
