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
            {"ABD_PAIN", "Abdominal Pain", 6, {
                {DepartmentType::GENERAL, 70}
            }},
            {"ARM_PAIN", "Arm or Shoulder Pain", 5, {
                {DepartmentType::CARDIAC, 70},
                {DepartmentType::GENERAL, 20}
            }},
            {"BACK_PAIN", "Back Pain", 4, {
                {DepartmentType::GENERAL, 60}
            }},
            {"BLEEDING", "Bleeding (Non-Respiratory)", 8, {
                {DepartmentType::GENERAL, 80}
            }},
            {"BLUE_LIPS", "Blue Lips or Nails", 9, {
                {DepartmentType::CARDIAC, 80},
                {DepartmentType::RESPIRATORY, 80}
            }},
            {"CHEST_PAIN", "Chest Pain", 9, {
                {DepartmentType::CARDIAC, 90},
                {DepartmentType::RESPIRATORY, 20}
            }},
            {"CHEST_TIGHT", "Chest Tightness", 7, {
                {DepartmentType::RESPIRATORY, 75},
                {DepartmentType::CARDIAC, 65}
            }},
            {"COLD_SWEATS", "Cold Sweats", 6, {
                {DepartmentType::CARDIAC, 70},
                {DepartmentType::GENERAL, 25}
            }},
            {"COUGH", "Coughing", 4, {
                {DepartmentType::RESPIRATORY, 70},
                {DepartmentType::CARDIAC, 10}
            }},
            {"COUGHING_BLOOD", "Coughing Blood", 9, {
                {DepartmentType::RESPIRATORY, 95},
                {DepartmentType::GENERAL, 20}
            }},
            {"DIARRHEA", "Diarrhea", 3, {
                {DepartmentType::GENERAL, 55}
            }},
            {"DIFFICULTY_SPEAK", "Difficulty Speaking", 7, {
                {DepartmentType::RESPIRATORY, 75},
                {DepartmentType::GENERAL, 25}
            }},
            {"DIZZY_FAINT", "Dizziness or Fainting", 6, {
                {DepartmentType::CARDIAC, 75},
                {DepartmentType::GENERAL, 30}
            }},
            {"EXERCISE_INTOL", "Exercise Intolerance", 5, {
                {DepartmentType::CARDIAC, 65},
                {DepartmentType::RESPIRATORY, 30}
            }},
            {"FATIGUE", "Severe Fatigue", 4, {
                {DepartmentType::CARDIAC, 50},
                {DepartmentType::RESPIRATORY, 40},
                {DepartmentType::GENERAL, 30}
            }},
            {"FEVER", "Fever", 5, {
                {DepartmentType::GENERAL, 40},
                {DepartmentType::RESPIRATORY, 40}
            }},
            {"HEADACHE", "Headache", 4, {
                {DepartmentType::GENERAL, 65},
                {DepartmentType::CARDIAC, 10}
            }},
            {"HEART_PALP", "Heart Palpitations", 7, {
                {DepartmentType::CARDIAC, 80}
            }},
            {"JOINT_PAIN", "Joint Pain/Swelling", 4, {
                {DepartmentType::GENERAL, 55}
            }},
            {"LEG_SWELLING", "Leg Swelling", 4, {
                {DepartmentType::CARDIAC, 60},
                {DepartmentType::GENERAL, 20}
            }},
            {"NASAL_CONGEST", "Nasal Congestion", 2, {
                {DepartmentType::RESPIRATORY, 50}
            }},
            {"NAUSEA", "Nausea/Vomiting", 5, {
                {DepartmentType::GENERAL, 60}
            }},
            {"RAPID_PULSE", "Rapid or Irregular Pulse", 8, {
                {DepartmentType::CARDIAC, 85}
            }},
            {"RASH", "Skin Rash", 3, {
                {DepartmentType::GENERAL, 50}
            }},
            {"SHORTNESS_BREATH", "Shortness of Breath", 8, {
                {DepartmentType::CARDIAC, 60},
                {DepartmentType::RESPIRATORY, 60}
            }},
            {"SLEEP_APNEA", "Sleep Apnea Symptoms", 5, {
                {DepartmentType::RESPIRATORY, 65}
            }},
            {"SORE_THROAT", "Sore Throat", 3, {
                {DepartmentType::RESPIRATORY, 60},
                {DepartmentType::GENERAL, 20}
            }},
            {"URINARY", "Urinary Problems", 5, {
                {DepartmentType::GENERAL, 65}
            }},
            {"WHEEZING", "Wheezing", 7, {
                {DepartmentType::RESPIRATORY, 85},
                {DepartmentType::CARDIAC, 15}
            }}
        };
        return symptoms;
    }

    static const PresetSymptom* findSymptomById(const std::string& id);
};

#endif
