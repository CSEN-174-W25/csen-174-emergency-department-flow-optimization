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

int Symptoms::calculateOverallUrgency() const {
    if (_symptoms.empty()) {
        return 10; // Lowest urgency
    }

    // Use the most urgent symptom as the base urgency
    int mostUrgent = 10; // Start with lowest urgency (10)
    int totalWeight = 0;
    int weightedSum = 0;

    // Calculate weighted average with more weight given to more urgent symptoms
    for (const auto& symptom : _symptoms) {
        int urgency = symptom.calculateUrgency();
        // More urgent symptoms (lower numbers) get more weight
        int weight = 11 - urgency; // Weight from 1-10
        weightedSum += urgency * weight;
        totalWeight += weight;

        // Track most urgent symptom (lowest number)
        mostUrgent = std::min(mostUrgent, urgency);
    }

    // Calculate weighted average, but bias toward more urgent symptoms
    int weightedAvg = totalWeight > 0 ? weightedSum / totalWeight : 10;

    // Final urgency leans toward the most urgent symptom but considers the average
    // 70% influence from most urgent symptom, 30% from weighted average
    int finalUrgency = (7 * mostUrgent + 3 * weightedAvg) / 10;

    // Ensure it stays in range 1-10
    return std::max(1, std::min(10, finalUrgency));
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

int Symptoms::PatientSymptom::calculateUrgency() const {
    const auto* def = SymptomDefinition::findSymptomById(symptomId);
    if (!def) return 10; // Lowest urgency

    // Original calculation gave high numbers for urgent symptoms
    int originalUrgency = def->baseUrgency;

    // Adjust based on patient-reported severity (1-5)
    // Severity 5 should make it more urgent (lower number in new scale)
    // Severity 1 should make it less urgent (higher number in new scale)

    // Map the 1-5 severity directly to priority contribution
    // Severity 5 contributes -2 to priority (making it more urgent)
    // Severity 1 contributes +2 to priority (making it less urgent)
    int severityAdjustment = 3 - severityRating;

    // Calculate final urgency (1-10 scale, 1 is most urgent)
    int finalUrgency = std::max(1, std::min(10, 11 - originalUrgency + severityAdjustment));

    return finalUrgency;
}
