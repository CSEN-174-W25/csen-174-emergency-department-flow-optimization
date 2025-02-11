#include "test_cases.h"
//#include <QtTest>

test_cases::test_cases()
{

}

void test_cases::test_add_symptom()
{
    Symptoms symptoms;

    // Test correct symptom addition
    QVERIFY(symptoms.addSymptom("CHEST_PAIN", 3));
    QVERIFY(symptoms.hasSymptom("CHEST_PAIN"));

    // Test invalid severity rating (should be 1-5)
    QVERIFY(!symptoms.addSymptom("FEVER", 6));
    QVERIFY(!symptoms.addSymptom("FEVER", 0));

    // Test invalid symptom ID
    QVERIFY(!symptoms.addSymptom("DOES_NOT_EXIST", 3));

    // Test duplicate symptom
    QVERIFY(!symptoms.addSymptom("CHEST_PAIN", 4));

    // Test 5 symptom limit
    QVERIFY(symptoms.addSymptom("FEVER", 3));
    QVERIFY(symptoms.addSymptom("COUGH", 2));
    QVERIFY(symptoms.addSymptom("SHORTNESS_BREATH", 4));
    QVERIFY(symptoms.addSymptom("ABD_PAIN", 3));
    QVERIFY(!symptoms.addSymptom("NAUSEA", 2)); // Should fail as we've hit MAX_SYMPTOMS = 5
}

void test_cases::test_remove_symptom()
{
    Symptoms symptoms;

    // Add and then remove a symptom
    symptoms.addSymptom("CHEST_PAIN", 3);
    QVERIFY(symptoms.hasSymptom("CHEST_PAIN"));
    symptoms.removeSymptom("CHEST_PAIN");
    QVERIFY(!symptoms.hasSymptom("CHEST_PAIN"));

    // Try to remove non-existent symptom
    symptoms.removeSymptom("DOES_NOT_EXIST");
}

void test_cases::test_has_symptom()
{
    Symptoms symptoms;

    // Test empty symptoms list
    QVERIFY(!symptoms.hasSymptom("CHEST_PAIN"));

    // Test after adding symptom
    symptoms.addSymptom("CHEST_PAIN", 3);
    QVERIFY(symptoms.hasSymptom("CHEST_PAIN"));
    QVERIFY(!symptoms.hasSymptom("FEVER"));
}

void test_cases::test_get_detailed_department_recommendation()
{
    Symptoms symptoms;

    // Test cardiac symptoms
    symptoms.addSymptom("CHEST_PAIN", 5);
    symptoms.addSymptom("HEART_PALP", 4);
    auto rec = symptoms.getDetailedDepartmentRecommendation();
    QCOMPARE(rec.primaryDepartment, DepartmentType::CARDIAC);

    // Clear and test respiratory symptoms
    symptoms = Symptoms();
    symptoms.addSymptom("COUGH", 4);
    symptoms.addSymptom("SORE_THROAT", 3);
    rec = symptoms.getDetailedDepartmentRecommendation();
    QCOMPARE(rec.primaryDepartment, DepartmentType::RESPIRATORY);

    // Test overlapping symptoms
    symptoms = Symptoms();
    symptoms.addSymptom("SHORTNESS_BREATH", 5);
    rec = symptoms.getDetailedDepartmentRecommendation();
    QVERIFY(rec.hasSignificantOverlap);
}

void test_cases::test_calculate_overall_urgency()
{
    Symptoms symptoms;

    // Test empty symptoms
    QCOMPARE(symptoms.calculateOverallUrgency(), 0);

    // Test single symptom
    symptoms.addSymptom("CHEST_PAIN", 5); // High urgency symptom
    QVERIFY(symptoms.calculateOverallUrgency() > 5);

    // Test multiple symptoms
    symptoms.addSymptom("FEVER", 2); // Lower urgency symptom
    int urgency = symptoms.calculateOverallUrgency();
    QVERIFY(urgency > 0 && urgency <= 10);
}

void test_cases::test_get_symptoms()
{
    Symptoms symptoms;

    // Test empty symptoms list
    QVERIFY(symptoms.getSymptoms().empty());

    // Test after adding symptoms
    symptoms.addSymptom("CHEST_PAIN", 3);
    symptoms.addSymptom("FEVER", 2);
    auto symptomList = symptoms.getSymptoms();
    QCOMPARE(symptomList.size(), 2u);

    // Verify symptom contents
    bool hasChestPain = false;
    bool hasFever = false;
    for (const auto& symptom : symptomList) {
        if (symptom.symptomId == "CHEST_PAIN") hasChestPain = true;
        if (symptom.symptomId == "FEVER") hasFever = true;
    }
    QVERIFY(hasChestPain && hasFever);
}

void test_cases::test_get_symptom_count()
{
    Symptoms symptoms;

    // Test empty symptoms
    QCOMPARE(symptoms.getSymptomCount(), 0u);

    // Test after adding symptoms
    symptoms.addSymptom("CHEST_PAIN", 3);
    QCOMPARE(symptoms.getSymptomCount(), 1u);

    symptoms.addSymptom("FEVER", 2);
    QCOMPARE(symptoms.getSymptomCount(), 2u);

    // Test after removing symptom
    symptoms.removeSymptom("FEVER");
    QCOMPARE(symptoms.getSymptomCount(), 1u);
}

void test_cases::test_has_additional_symptoms()
{
    Symptoms symptoms;

    // Test default value
    QVERIFY(!symptoms.hasAdditionalSymptoms());
}

void test_cases::test_set_additional_symptoms()
{
    Symptoms symptoms;

    // Test setting to true
    symptoms.setAdditionalSymptoms(true);
    QVERIFY(symptoms.hasAdditionalSymptoms());

    // Test setting to false
    symptoms.setAdditionalSymptoms(false);
    QVERIFY(!symptoms.hasAdditionalSymptoms());
}

//QTEST_MAIN(test_cases)

//#include "test_cases.moc"
