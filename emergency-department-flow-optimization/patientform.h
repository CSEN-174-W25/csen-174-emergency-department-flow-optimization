#ifndef PATIENTFORM_H
#define PATIENTFORM_H

#include <QWidget>
#include "patient.h"

namespace Ui {
class PatientForm;
}

class PatientForm : public QWidget
{
        Q_OBJECT

    public:
        explicit PatientForm(QWidget *parent = nullptr);
        ~PatientForm();

    private slots:
        // Navigation buttons
        void on_nextButton_clicked();
        void on_backButton_clicked();
        void on_cancelButton_clicked();

        // Form validation and submission
        void validateCurrentPage();
        void submitForm();

        // Symptom selection
        void on_addSymptomButton_clicked();
        void on_removeSymptomButton_clicked();
        void updateSymptomList();

    private:
        Ui::PatientForm *ui;
        Patient currentPatient;
        int currentPage;
        static const int TOTAL_PAGES = 4;

        // Page setup methods
        void setupPersonalInfoPage();
        void setupInsurancePage();
        void setupSymptomsPage();
        void setupMedicalHistoryPage();

        // Helper methods
        void showPage(int pageIndex);
        bool validatePersonalInfo();
        bool validateInsurance();
        bool validateSymptoms();
        bool validateMedicalHistory();
};

#endif
