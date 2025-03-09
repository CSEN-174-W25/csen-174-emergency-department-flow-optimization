#include "symptoms.h"
#include <algorithm>

const size_t Symptoms::MAX_SYMPTOMS;
// In symptoms.cpp, update the addSymptom implementation:
bool Symptoms::addSymptom(const std::string& symptomId, const std::string& symptomName, int severityRating, bool nurseOverride) {
    // Check severity range
    if (severityRating < 1 || severityRating > 5) {
        return false;
    }

    // Verify symptom exists in preset list
    if (!SymptomDefinition::findSymptomById(symptomId)) {
        return false;
    }

    // Check if symptom already exists
    if (hasSymptom(symptomId)) {
        return false;
    }

    // Check maximum symptoms limit only if not a nurse override
    if (!nurseOverride && _symptoms.size() >= MAX_SYMPTOMS) {
        return false;
    }

    PatientSymptom symptom{symptomId, symptomName, severityRating};
    _symptoms.push_back(symptom);
    return true;
}

void Symptoms::removeSymptom(const std::string& symptomId) {
    auto it = std::find_if(_symptoms.begin(), _symptoms.end(),
                          [&symptomId](const PatientSymptom& s) {
                              return s.symptomId == symptomId;
                          });
    if (it != _symptoms.end()) {
        _symptoms.erase(it);
    }
}

bool Symptoms::hasSymptom(const std::string& symptomId) const {
    return std::any_of(_symptoms.begin(), _symptoms.end(),
                      [&symptomId](const PatientSymptom& s) {
                          return s.symptomId == symptomId;
                      });
}

int Symptoms::PatientSymptom::calculateUrgency() const {
    const auto* def = SymptomDefinition::findSymptomById(symptomId);
    if (!def) return 0;
    // Combine base urgency with patient-reported severity
    return (def->baseUrgency * 2 + severityRating) / 3;
}

Symptoms::DepartmentRecommendation Symptoms::getDetailedDepartmentRecommendation() const {
    std::map<DepartmentType, DepartmentScore> departmentScores;
    
    // Calculate scores for each department
    for (const auto& symptom : _symptoms) {
        const auto* def = SymptomDefinition::findSymptomById(symptom.symptomId);
        if (!def) continue;
        
        // Add weighted scores for each department this symptom affects
        for (const auto& [dept, weight] : def->departmentWeights) {
            auto& score = departmentScores[dept];
            score.department = dept;
            score.score += weight * symptom.severityRating;
            score.contributingSymptoms.push_back(def->name);
        }
    }
    
    // Convert to vector and sort
    std::vector<DepartmentScore> sortedScores;
    for (const auto& [dept, score] : departmentScores) {
        sortedScores.push_back(score);
    }
    std::sort(sortedScores.rbegin(), sortedScores.rend());
    
    DepartmentRecommendation recommendation;
    recommendation.allDepartmentScores = sortedScores;
    
    // Determine primary department and check for significant overlap
    if (!sortedScores.empty()) {
        recommendation.primaryDepartment = sortedScores[0].department;
        recommendation.hasSignificantOverlap = 
            sortedScores.size() > 1 && 
            static_cast<double>(sortedScores[1].score) / sortedScores[0].score > 0.8;
    } else {
        recommendation.primaryDepartment = DepartmentType::GENERAL;
        recommendation.hasSignificantOverlap = false;
    }
    
    return recommendation;
}

int Symptoms::calculateOverallUrgency() const {
    if (_symptoms.empty()) {
        return 0;
    }
    
    int totalUrgency = 0;
    for (const auto& symptom : _symptoms) {
        totalUrgency += symptom.calculateUrgency();
    }
    
    return totalUrgency / static_cast<int>(_symptoms.size());
}
