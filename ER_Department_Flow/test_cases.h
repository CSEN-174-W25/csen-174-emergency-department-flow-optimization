#ifndef TEST_FUNCTIONS_H
#define TEST_FUNCTIONS_H

#include <QObject>
#include <QTest>
#include "symptoms.h"
#include "symptom_definition.h"

class test_cases: public QObject
{
    Q_OBJECT
public:
    test_cases();

private slots:
    // Symptoms tests
    void test_add_symptom();
    void test_remove_symptom();
    void test_has_symptom();
    void test_get_detailed_department_recommendation();
    void test_calculate_overall_urgency();
    void test_get_symptoms();
    void test_get_symptom_count();
    void test_has_additional_symptoms();
    void test_set_additional_symptoms();
};

#endif // TESTS_H
