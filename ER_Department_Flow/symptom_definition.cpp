#include "symptom_definition.h"

// Implementation of findSymptomById:
// Iterates over the preset symptoms and returns a pointer to the one
// whose id matches the provided id. If not found, returns nullptr.
const SymptomDefinition::PresetSymptom* SymptomDefinition::findSymptomById(const std::string& id) {
    const auto& symptoms = getPresetSymptoms();
    for (const auto& symptom : symptoms) {
        if (symptom.id == id) {
            return &symptom;
        }
    }
    return nullptr;
}
