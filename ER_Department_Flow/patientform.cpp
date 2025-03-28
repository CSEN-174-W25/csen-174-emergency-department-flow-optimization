#include "patientform.h"
#include "ui_patientform.h"
#include "patientdatabase.h"
#include "department.h"
#include "globaldepartments.h"
#include <QMessageBox>
#include <QDate>
#include <QDebug>

PatientForm::PatientForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientForm),
    currentPage(0)
{
    ui->setupUi(this);
    // Make the 'Next' and 'Submit' buttons blue
    QString blueButtonStyle = "background-color: #0070a4; color: white; font-weight: bold;";
    ui->nextButton->setStyleSheet(blueButtonStyle);
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

void PatientForm::on_nextButton_clicked()
{
    qDebug() << "Next button clicked, current page:" << currentPage;
    // Validate the current page
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

    if (isValid) {
        if (currentPage < TOTAL_PAGES - 1) {
            currentPage++;
            showPage(currentPage);
        } else {
            submitForm();
        }
    }
}


void PatientForm::on_backButton_clicked()
{
    qDebug() << "Back button clicked, current page:" << currentPage;
    if (currentPage > 0) {
        currentPage--;
        showPage(currentPage);
    }
}

void PatientForm::on_cancelButton_clicked()
{
    // Ask the user to confirm cancellation
    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Confirm Cancellation",
                                                              "Are you sure you want to cancel? Any information you've entered will be lost.",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        qDebug() << "Cancel button clicked, confirmed by user.";
        // If the main window is the parent, re-show it
        QWidget* parent = this->parentWidget();
        if (parent) {
            parent->show();
        }

        // Then close the patient form
        this->close();
    }
    // If No, just return and do nothing
}

void PatientForm::setupPersonalInfoPage()
{
    // Setup date picker for date of birth
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
    // Insurance radio button should be unchecked by default
    ui->hasInsuranceRadio->setChecked(false);
    ui->insuranceGroupBox->setEnabled(false);

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
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(symptom.name));
        // Store the ID in the item using a user role
        item->setData(Qt::UserRole, QString::fromStdString(symptom.id));
        ui->symptomList->addItem(item);
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

    // Handle empty address
    std::string address = ui->addressTextEdit->toPlainText().toStdString();
    if (address.empty()) {
        address = "None";
    }
    currentPatient.setHomeAddr(address);

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
    } else {
        // If no insurance is selected, set default values
        currentPatient.setInsuranceProvider("None");
        currentPatient.setInsuranceMemberId("None");
    }
    return true;
}

void PatientForm::on_addSymptomButton_clicked()
{
    QListWidgetItem* currentItem = ui->symptomList->currentItem();
    if (currentItem) {
        // Retrieve the stored symptom ID
        QString symptomName = currentItem->text();
        QString symptomId = currentItem->data(Qt::UserRole).toString();
        int severity = ui->severitySpinBox->value();

        // Add to patient's symptoms using the symptom ID.
        bool added = currentPatient.getSymptoms().addSymptom(
            symptomId.toStdString(), symptomName.toStdString(), severity
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
    QListWidgetItem* currentItem = ui->selectedSymptomList->currentItem();
    if (currentItem) {
        // Extract the symptom name from the displayed string
        QString fullText = currentItem->text();
        QString symptomName = fullText.split(" - ").first();

        // Find the corresponding symptom ID
        for (const auto& symptom : currentPatient.getSymptoms().getSymptoms()) {
            if (QString::fromStdString(symptom.symptomName) == symptomName) {
                currentPatient.getSymptoms().removeSymptom(symptom.symptomId);
                break;
            }
        }

        updateSymptomList();
    }
}

void PatientForm::updateSymptomList()
{
    ui->selectedSymptomList->clear();
    for (const auto& symptom : currentPatient.getSymptoms().getSymptoms()) {
        QString itemText = QString::fromStdString(symptom.symptomName) + " - Severity: " + QString::number(symptom.severityRating);
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
    // Save medical history information with defaults if patient leaves them empty
    std::string medicalHistory = ui->medicalHistoryTextEdit->toPlainText().toStdString();
    if (medicalHistory.empty()) {
        medicalHistory = "None";
    }
    currentPatient.setMedicalHistory(medicalHistory);

    std::string familyHistory = ui->familyHistoryTextEdit->toPlainText().toStdString();
    if (familyHistory.empty()) {
        familyHistory = "None";
    }
    currentPatient.setFamilyHistory(familyHistory);

    std::string medications = ui->medicationsTextEdit->toPlainText().toStdString();
    if (medications.empty()) {
        medications = "None";
    }
    currentPatient.setCurrentMedications(medications);

    if (ui->allergiesCheckBox->isChecked()) {
        std::string allergies = ui->allergiesTextEdit->toPlainText().toStdString();
        if (allergies.empty()) {
            allergies = "None";
        }
        currentPatient.setAllergies(allergies);
    } else {
        currentPatient.setAllergies("None");
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

    // Determine the recommended department type
    DepartmentType deptType = recommendation.primaryDepartment;
    
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
    
    // Generate a new Patient ID, then store the patient in the database
    int newPatientId = PatientDatabase::instance().generatePatientId();
    currentPatient.setPatientId(newPatientId);
    PatientDatabase::instance().storePatient(currentPatient);

    // Add the patient to the department queue using the overall urgency
    int priority = currentPatient.getSymptoms().calculateOverallUrgency();

    extern Department cardiacDept;
    extern Department respiratoryDept;
    extern Department generalDept;

    Department* targetDept = nullptr;
    switch (deptType) {
    case DepartmentType::CARDIAC:
        targetDept = &cardiacDept;
        break;
    case DepartmentType::RESPIRATORY:
        targetDept = &respiratoryDept;
        break;
    case DepartmentType::GENERAL:
        targetDept = &generalDept;
        break;
    default:
        targetDept = &generalDept;
    }
    if (targetDept) {
        targetDept->addPatient(newPatientId, priority);
    }
    
    // Return to main window
    qDebug() << "Parent widget:" << this->parentWidget();
    QWidget* parent = this->parentWidget();
    if (parent) {
        parent->show();
    }
    this->close();
}
