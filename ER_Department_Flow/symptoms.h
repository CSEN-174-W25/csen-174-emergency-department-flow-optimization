#ifndef SYMPTOMS_H
#define SYMPTOMS_H

#include "symptom_definition.h"

class Symptoms {
public:
    struct PatientSymptom {
        std::string symptomId;
        std::string symptomName; //added symptomName
        int severityRating;  // 1-5
        
        int calculateUrgency() const;
    };

    struct DepartmentRecommendation {
        DepartmentType primaryDepartment;
        std::vector<DepartmentScore> allDepartmentScores;
        bool hasSignificantOverlap;
    };

    Symptoms() = default;

    bool addSymptom(const std::string& symptomId, const std::string& symptomName, int severityRating);
    void removeSymptom(const std::string& symptomId);
    bool hasSymptom(const std::string& symptomId) const;
    
    DepartmentRecommendation getDetailedDepartmentRecommendation() const;
    int calculateOverallUrgency() const;

    static const size_t MAX_SYMPTOMS = 5;
    
    const std::vector<PatientSymptom>& getSymptoms() const { return _symptoms; }
    size_t getSymptomCount() const { return _symptoms.size(); }
    bool hasAdditionalSymptoms() const { return _hasAdditionalSymptoms; }
    void setAdditionalSymptoms(bool has) { _hasAdditionalSymptoms = has; }

private:
    std::vector<PatientSymptom> _symptoms;
    bool _hasAdditionalSymptoms = false;
    //static const size_t MAX_SYMPTOMS = 5;
};
#endif
