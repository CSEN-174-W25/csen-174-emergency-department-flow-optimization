#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "main.h"
#include "symptoms.h"
#include <ctime>
#include <string>
#include <vector>
#include <queue>
#include <map>

class Department {
public:
    struct QueueEntry {
        int patientId;
        int priority;
        std::time_t entryTime;
        
        bool operator<(const QueueEntry& other) const {
            return priority < other.priority;
        }
    };

    Department(const std::string& name);
    Department();
    
    // Queue management
    void addPatient(int patientId, int priority);
    void addPatient(int patientId, int priority, std::time_t entryTime);
    void removePatient(int patientId);
    void updatePatientPriority(int patientId, int newPriority);
    std::vector<QueueEntry> getQueue() const;
    
    // Department info
    std::string getName() const;
    int getPatientCount() const;
    bool hasPatient(int patientId) const;
    
    // For nurse override functionality
    void transferPatient(int patientId, Department& targetDept);
    
private:
    std::string _name;
    std::priority_queue<QueueEntry> _priorityQueue;
    std::map<int, QueueEntry> _patientIndex; // For O(1) lookups
};
#endif
