#include "patientform.h"
#include "ui_patientform.h"
#include <QMessageBox>
#include <QDate>

PatientForm::PatientForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientForm),
    currentPage(0)
{
    ui->setupUi(this);
    this->setWindowTitle("Patient Information");
    
    // Initial setup
    setupPersonalInfoPage();
    setupInsurancePage();
    setupSymptomsPage();
    setupMedicalHistoryPage();
    
    // Show first page
    showPage(0);
}

PatientForm::~PatientForm()
{
    delete ui;
}

//Navigation buttons, add the proper functionality add their functionality

void PatientForm::on_nextButton_clicked(){
    return;
}
void PatientForm::on_backButton_clicked(){
    return;
}
void PatientForm::on_cancelButton_clicked(){
    return;
}





void PatientForm::setupPersonalInfoPage()
{
    // Setup date picker for DOB
    ui->dobDateEdit->setMaximumDate(QDate::currentDate());
    ui->dobDateEdit->setDisplayFormat("MM/dd/yyyy");
    
    // Setup gender combo box
    ui->genderComboBox->addItem("Male");
    ui->genderComboBox->addItem("Female");
    ui->genderComboBox->addItem("Other");
    ui->genderComboBox->addItem("Prefer not to say");
}

void PatientForm::setupInsurancePage()
{
    // Setup insurance radio buttons
    connect(ui->hasInsuranceRadio, &QRadioButton::toggled, [this](bool checked) {
        ui->insuranceGroupBox->setEnabled(checked);
    });
}

void PatientForm::setupSymptomsPage()
{
    // Populate symptom list with preset symptoms
    ui->symptomList->clear();
    for (const auto& symptom : SymptomDefinition::getPresetSymptoms()) {
        ui->symptomList->addItem(QString::fromStdString(symptom.name));
    }
    
    // Setup severity rating
    ui->severitySpinBox->setRange(1, 5);
    ui->severitySpinBox->setValue(3);
    
    // Initialize selected symptoms list
    updateSymptomList();
}

void PatientForm::setupMedicalHistoryPage()
{
    // Setup any specific medical history page elements
    ui->allergiesCheckBox->setChecked(false);
    ui->allergiesTextEdit->setEnabled(false);
    
    connect(ui->allergiesCheckBox, &QCheckBox::toggled, 
            ui->allergiesTextEdit, &QTextEdit::setEnabled);
}

void PatientForm::showPage(int pageIndex)
{
    currentPage = pageIndex;
    ui->stackedWidget->setCurrentIndex(pageIndex);
    
    // Update button states
    ui->backButton->setEnabled(pageIndex > 0);
    ui->nextButton->setText(pageIndex == TOTAL_PAGES - 1 ? "Submit" : "Next");
}

bool PatientForm::validatePersonalInfo()
{
    // Check required fields
    if (ui->nameLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please enter your name.");
        return false;
    }
    
    if (ui->contactLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please enter your contact number.");
        return false;
    }
    
    if (ui->emergencyContactLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please enter an emergency contact number.");
        return false;
    }
    
    // Save to current patient
    currentPatient.setName(ui->nameLineEdit->text().toStdString());
    currentPatient.setGender(ui->genderComboBox->currentText().toStdString());
    currentPatient.setDOB(ui->dobDateEdit->date());
    currentPatient.setContact(ui->contactLineEdit->text().toStdString());
    currentPatient.setEmergencyContact(ui->emergencyContactLineEdit->text().toStdString());
    currentPatient.setHomeAddr(ui->addressTextEdit->toPlainText().toStdString());
    
    return true;
}

bool PatientForm::validateInsurance()
{
    if (ui->hasInsuranceRadio->isChecked()) {
        if (ui->providerLineEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "Please enter your insurance provider.");
            return false;
        }
        if (ui->memberIdLineEdit->text().isEmpty()) {
            QMessageBox::warning(this, "Validation Error", "Please enter your member ID.");
            return false;
        }
        
        // Save insurance information
        currentPatient.setInsuranceProvider(ui->providerLineEdit->text().toStdString());
        currentPatient.setInsuranceMemberId(ui->memberIdLineEdit->text().toStdString());
    }
    return true;
}

void PatientForm::on_addSymptomButton_clicked()
{
    if (ui->symptomList->currentItem()) {
        QString symptom = ui->symptomList->currentItem()->text();
        int severity = ui->severitySpinBox->value();
        
        // Add to patient's symptoms
        bool added = currentPatient.getSymptoms().addSymptom(
            symptom.toStdString(), severity
        );
        
        if (!added) {
            QMessageBox::warning(this, "Warning", 
                "Maximum number of symptoms (5) reached or symptom already added.");
            return;
        }
        
        updateSymptomList();
    }
}

void PatientForm::on_removeSymptomButton_clicked()
{
    if (ui->selectedSymptomList->currentItem()) {
        QString symptom = ui->selectedSymptomList->currentItem()->text();
        currentPatient.getSymptoms().removeSymptom(symptom.split(" - ")[0].toStdString());
        updateSymptomList();
    }
}

void PatientForm::updateSymptomList()
{
    ui->selectedSymptomList->clear();
    for (const auto& symptom : currentPatient.getSymptoms().getSymptoms()) {
        QString itemText = QString::fromStdString(symptom.symptomId) + 
                          " - Severity: " + QString::number(symptom.severityRating);
        ui->selectedSymptomList->addItem(itemText);
    }
    
    // Update add button state
    ui->addSymptomButton->setEnabled(
        currentPatient.getSymptoms().getSymptomCount() < Symptoms::MAX_SYMPTOMS
    );
}

bool PatientForm::validateSymptoms()
{
    if (currentPatient.getSymptoms().getSymptomCount() == 0) {
        QMessageBox::warning(this, "Validation Error", 
            "Please select at least one symptom.");
        return false;
    }
    return true;
}

bool PatientForm::validateMedicalHistory()
{
    // Save medical history information
    currentPatient.setMedicalHistory(ui->medicalHistoryTextEdit->toPlainText().toStdString());
    currentPatient.setFamilyHistory(ui->familyHistoryTextEdit->toPlainText().toStdString());
    currentPatient.setCurrentMedications(ui->medicationsTextEdit->toPlainText().toStdString());
    
    if (ui->allergiesCheckBox->isChecked()) {
        currentPatient.setAllergies(ui->allergiesTextEdit->toPlainText().toStdString());
    }
    
    return true;
}

void PatientForm::validateCurrentPage()
{
    bool isValid = false;
    
    switch (currentPage) {
        case 0:
            isValid = validatePersonalInfo();
            break;
        case 1:
            isValid = validateInsurance();
            break;
        case 2:
            isValid = validateSymptoms();
            break;
        case 3:
            isValid = validateMedicalHistory();
            break;
        default:
            isValid = true;
    }
    
    if (isValid && currentPage < TOTAL_PAGES - 1) {
        showPage(currentPage + 1);
    }
}

void PatientForm::submitForm()
{
    // Perform final validation
    if (!validateMedicalHistory()) {
        return;
    }
    
    // Get department recommendation
    auto recommendation = currentPatient.getSymptoms().getDetailedDepartmentRecommendation();
    
    // Show confirmation with department assignment
    QString deptName;
    switch (recommendation.primaryDepartment) {
        case DepartmentType::CARDIAC:
            deptName = "Cardiac";
            break;
        case DepartmentType::RESPIRATORY:
            deptName = "Respiratory";
            break;
        case DepartmentType::GENERAL:
            deptName = "General";
            break;
        default:
            deptName = "Unknown";
    }
    
    QMessageBox::information(this, "Submission Successful",
        "Your information has been submitted.\n\n"
        "Based on your symptoms, you have been assigned to the " + 
        deptName + " department.\n\n"
        "Please wait to be called by a nurse.");
    
    // TODO: Add patient to department queue
    
    // Return to main window
    this->parentWidget()->show();
    this->hide();
}
