#ifndef SYMPTOM_DEFINITIONS_H
#define SYMPTOM_DEFINITIONS_H

#include <string>
#include <vector>
#include <map>
#include <set>

enum class DepartmentType {
    CARDIAC,
    RESPIRATORY,
    GENERAL,
    UNKNOWN
};

struct DepartmentScore {
    DepartmentType department;
    int score;
    std::vector<std::string> contributingSymptoms;
    
    bool operator<(const DepartmentScore& other) const {
        return score < other.score;
    }
};

class SymptomDefinition {
public:
    struct PresetSymptom {
        std::string id;
        std::string name;
        int baseUrgency;  // 1-10
        std::vector<std::pair<DepartmentType, int>> departmentWeights;
    };

    static const std::vector<PresetSymptom>& getPresetSymptoms() {
        static const std::vector<PresetSymptom> symptoms = {
            // Cardiac Department Primary Symptoms
            {"CHEST_PAIN", "Chest Pain", 9, {
                {DepartmentType::CARDIAC, 90},
                {DepartmentType::RESPIRATORY, 20}
            }},
            {"HEART_PALP", "Heart Palpitations", 7, {
                {DepartmentType::CARDIAC, 80}
            }},
            
            // Respiratory Department Primary Symptoms
            {"COUGH", "Coughing", 4, {
                {DepartmentType::RESPIRATORY, 70},
                {DepartmentType::CARDIAC, 10}
            }},
            {"SORE_THROAT", "Sore Throat", 3, {
                {DepartmentType::RESPIRATORY, 60},
                {DepartmentType::GENERAL, 20}
            }},
            
            // Overlapping Symptoms
            {"SHORTNESS_BREATH", "Shortness of Breath", 8, {
                {DepartmentType::CARDIAC, 60},
                {DepartmentType::RESPIRATORY, 60}
            }},
            {"FEVER", "Fever", 5, {
                {DepartmentType::GENERAL, 40},
                {DepartmentType::RESPIRATORY, 40}
            }},
            
            // General Department Primary Symptoms
            {"ABD_PAIN", "Abdominal Pain", 6, {
                {DepartmentType::GENERAL, 70}
            }},
            {"NAUSEA", "Nausea/Vomiting", 5, {
                {DepartmentType::GENERAL, 60}
            }}
        };
        return symptoms;
    }

    static const PresetSymptom* findSymptomById(const std::string& id);
};

#endif
