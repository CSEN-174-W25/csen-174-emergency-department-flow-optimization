#include "edit_symptoms_dialog.h"
#include "ui_edit_symptoms_dialog.h"
#include <QMessageBox>

EditSymptomsDialog::EditSymptomsDialog(Patient* patient, Department* currentDept, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditSymptomsDialog),
    _patient(patient),
    _currentDept(currentDept)
{
    ui->setupUi(this);
    this->setWindowTitle("Edit Patient Symptoms");

    // Setup severity spinbox
    ui->severitySpinBox->setRange(1, 5);
    ui->severitySpinBox->setValue(3);

    // Initialize lists
    updateSymptomList();
    updateAvailableSymptoms();
}

EditSymptomsDialog::~EditSymptomsDialog()
{
    delete ui;
}

void EditSymptomsDialog::updateSymptomList()
{
    ui->currentSymptomsList->clear();
    for (const auto& symptom : _patient->getSymptoms().getSymptoms()) {
        QString itemText = QString::fromStdString(symptom.symptomName) + 
                         " - Severity: " + QString::number(symptom.severityRating);
        ui->currentSymptomsList->addItem(itemText);
    }
}

void EditSymptomsDialog::updateAvailableSymptoms()
{
    ui->availableSymptomsList->clear();
    
    // Get all current symptom IDs
    std::set<std::string> currentSymptomIds;
    for (const auto& symptom : _patient->getSymptoms().getSymptoms()) {
        currentSymptomIds.insert(symptom.symptomId);
    }
    
    // Add all symptoms that aren't currently assigned
    for (const auto& symptom : SymptomDefinition::getPresetSymptoms()) {
        if (currentSymptomIds.find(symptom.id) == currentSymptomIds.end()) {
            QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(symptom.name));
            item->setData(Qt::UserRole, QString::fromStdString(symptom.id));
            ui->availableSymptomsList->addItem(item);
        }
    }
}

void EditSymptomsDialog::on_addSymptomButton_clicked()
{
    QListWidgetItem* currentItem = ui->availableSymptomsList->currentItem();
    if (currentItem) {
        QString symptomId = currentItem->data(Qt::UserRole).toString();
        QString symptomName = currentItem->text();
        int severity = ui->severitySpinBox->value();

        // Add symptom without MAX_SYMPTOMS check
        _patient->getSymptoms().addSymptom(
            symptomId.toStdString(),
            symptomName.toStdString(),
            severity,
            true  // bypass max symptoms check
        );

        updateSymptomList();
        updateAvailableSymptoms();
    }
}

void EditSymptomsDialog::on_removeSymptomButton_clicked()
{
    QListWidgetItem* currentItem = ui->currentSymptomsList->currentItem();
    if (currentItem) {
        QString fullText = currentItem->text();
        QString symptomName = fullText.split(" - ").first();
        
        // Find and remove the symptom
        for (const auto& symptom : _patient->getSymptoms().getSymptoms()) {
            if (QString::fromStdString(symptom.symptomName) == symptomName) {
                _patient->getSymptoms().removeSymptom(symptom.symptomId);
                break;
            }
        }
        
        updateSymptomList();
        updateAvailableSymptoms();
    }
}

void EditSymptomsDialog::on_saveButton_clicked()
{
    // Recalculate priority based on new symptoms
    auto recommendation = _patient->getSymptoms().getDetailedDepartmentRecommendation();
    int newPriority = _patient->getSymptoms().calculateOverallUrgency();
    
    // Update patient's priority in the current department
    _currentDept->updatePatientPriority(_patient->getPatientId(), newPriority);
    
    accept();
}

void EditSymptomsDialog::on_cancelButton_clicked()
{
    reject();
}