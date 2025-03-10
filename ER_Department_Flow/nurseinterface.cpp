#include "nurseinterface.h"
#include "ui_nurseinterface.h"
#include "patientdatabase.h"
#include "globaldepartments.h"
#include "symptom_definition.h"
#include "vitals_dialog.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QString>
#include <QDebug>
#include <QComboBox>

NurseInterface::NurseInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NurseInterface)
    //cardiacDept("Cardiac"),
    //respiratoryDept("Respiratory"),
    //generalDept("General")
{
    ui->setupUi(this);
    this->setWindowTitle("Nurse Interface");
    
    // Setup refresh timer
    refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, &NurseInterface::updateQueues);
    refreshTimer->start(10000);  // Refresh every 10 seconds
    
    setupDepartmentViews();
    updateQueues();
}

NurseInterface::~NurseInterface()
{
    delete ui;
    delete refreshTimer;
}

void NurseInterface::setupDepartmentViews()
{
    // Setup table headers and properties for each department view
    QStringList headers;
    headers << "Patient ID" << "Name" << "Priority" << "Wait Time" << "Vitals" << "Symptoms";

    // Define style to remove default selection tint
    QString tableStyle = "QTableWidget {"
                         "  selection-background-color: #3D3D3D;"
                         "}"
                         "QTableWidget::item:!selected {"
                         "  background-color: transparent;"
                         "}";

    // Cardiac Department Table
    ui->cardiacTable->setColumnCount(6);
    ui->cardiacTable->setHorizontalHeaderLabels(headers);
    ui->cardiacTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->cardiacTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->cardiacTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->cardiacTable->setAlternatingRowColors(false);
    ui->cardiacTable->setStyleSheet(tableStyle);

    // Respiratory Department Table
    ui->respiratoryTable->setColumnCount(6);
    ui->respiratoryTable->setHorizontalHeaderLabels(headers);
    ui->respiratoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->respiratoryTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->respiratoryTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->respiratoryTable->setAlternatingRowColors(false);
    ui->respiratoryTable->setStyleSheet(tableStyle);

    // General Department Table
    ui->generalTable->setColumnCount(6);
    ui->generalTable->setHorizontalHeaderLabels(headers);
    ui->generalTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->generalTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->generalTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->generalTable->setAlternatingRowColors(false);
    ui->generalTable->setStyleSheet(tableStyle);
}

// Update the updateDepartmentView function to show the vitals status:
void NurseInterface::updateDepartmentView(const Department& dept, QTableWidget* table)
{
    table->setRowCount(0);  // Clear existing rows

    auto queue = dept.getQueue();
    for (const auto& entry : queue) {
        int row = table->rowCount();
        table->insertRow(row);

        // Get patient information
        Patient* patient = findPatient(entry.patientId);
        if (!patient) continue;

        // Calculate wait time
        QDateTime entryTime = QDateTime::fromSecsSinceEpoch(entry.entryTime);
        QString waitTime = calculateWaitTime(entryTime);

        // Add patient information to table
        QTableWidgetItem* patientId = new QTableWidgetItem(QString::number(entry.patientId));
        QTableWidgetItem* patientName = new QTableWidgetItem(QString::fromStdString(patient->getName()));
        QTableWidgetItem* patientPriority = new QTableWidgetItem(QString::number(entry.priority));
        QTableWidgetItem* patientWaitTime = new QTableWidgetItem(waitTime);

        // Add vitals status
        QTableWidgetItem* vitalsStatus = new QTableWidgetItem();
        if (patient->hasVitalsRecorded()) {
            vitalsStatus->setText("Recorded");
            vitalsStatus->setBackground(QColor(200, 255, 200)); // Light green
        } else {
            vitalsStatus->setText("Needed");
            vitalsStatus->setBackground(QColor(255, 200, 200)); // Light red
        }

        // Set flags
        patientId->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        patientName->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        patientPriority->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        patientWaitTime->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        vitalsStatus->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

        // Set items in table
        table->setItem(row, 0, patientId);
        table->setItem(row, 1, patientName);
        table->setItem(row, 2, patientPriority);
        table->setItem(row, 3, patientWaitTime);
        table->setItem(row, 4, vitalsStatus); // New column for vitals

        // Create symptoms string
        QString symptomsStr;
        for (const auto& symptom : patient->getSymptoms().getSymptoms()) {
            if (!symptomsStr.isEmpty()) symptomsStr += ", ";
            symptomsStr += QString::fromStdString(symptom.symptomName);
        }
        QTableWidgetItem* symptomsName = new QTableWidgetItem(symptomsStr);
        symptomsName->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        table->setItem(row, 5, symptomsName); // Moved to column 5
    }

    table->sortItems(2, Qt::DescendingOrder);  // Sort by priority
}

void NurseInterface::on_viewPatientButton_clicked()
{
    QTableWidget* currentTable = nullptr;
    
    // Determine which tab is active
    if (ui->departmentTabs->currentWidget() == ui->cardiacTab) {
        currentTable = ui->cardiacTable;
    } else if (ui->departmentTabs->currentWidget() == ui->respiratoryTab) {
        currentTable = ui->respiratoryTable;
    } else if (ui->departmentTabs->currentWidget() == ui->generalTab) {
        currentTable = ui->generalTable;
    }
    
    if (!currentTable || !currentTable->currentItem()) {
        QMessageBox::warning(this, "Error", "Please select a patient to view.");
        return;
    }
    
    int patientId = currentTable->item(currentTable->currentRow(), 0)->text().toInt();
    viewPatientDetails(patientId);
}

void NurseInterface::viewPatientDetails(int patientId)
{
    Patient* patient = findPatient(patientId);
    if (!patient) {
        QMessageBox::warning(this, "Error", "Patient not found.");
        return;
    }

    QString details = QString("Patient Details:\n\n"
                              "Name: %1\n"
                              "ID: %2\n"
                              "Gender: %3\n"
                              "DOB: %4\n\n"
                              "Contact: %5\n"
                              "Emergency Contact: %6\n\n"
                              "Insurance Provider: %7\n"
                              "Member ID: %8\n\n")
                          .arg(QString::fromStdString(patient->getName()))
                          .arg(patient->getPatientId())
                          .arg(QString::fromStdString(patient->getGender()))
                          .arg(patient->getDOB().toString("MM/dd/yyyy"))
                          .arg(QString::fromStdString(patient->getContact()))
                          .arg(QString::fromStdString(patient->getEmergencyContact()))
                          .arg(QString::fromStdString(patient->getInsuranceProvider()))
                          .arg(QString::fromStdString(patient->getInsuranceMemberId()));

    // Add vitals information if available
    if (patient->hasVitalsRecorded()) {
        details += QString("Vital Signs:\n"
                           "Heart Rate: %1 bpm\n"
                           "Blood Pressure: %2 mmHg\n"
                           "Blood Sugar: %3 mg/dL\n"
                           "Body Temperature: %4 °C\n"
                           "Blood Oxygen: %5%\n\n")
                       .arg(patient->getHeartRate())
                       .arg(QString::fromStdString(patient->getBloodPressure()))
                       .arg(patient->getBloodSugar())
                       .arg(QString::number(patient->getBodyTemperature(), 'f', 1))
                       .arg(patient->getBloodOxygen());
    } else {
        details += "Vital Signs: Not yet recorded\n\n";
    }

    details += QString("Medical History: %1\n\n"
                       "Current Medications: %2\n"
                       "Allergies: %3")
                   .arg(QString::fromStdString(patient->getMedicalHistory()))
                   .arg(QString::fromStdString(patient->getCurrentMedications()))
                   .arg(QString::fromStdString(patient->getAllergies()));

    QMessageBox::information(this, "Patient Details", details);
}

void NurseInterface::on_updatePriorityButton_clicked()
{
    QTableWidget* currentTable = nullptr;
    Department* currentDept = nullptr;
    
    // Determine which tab is active
    if (ui->departmentTabs->currentWidget() == ui->cardiacTab) {
        currentTable = ui->cardiacTable;
        currentDept = &::cardiacDept;
    } else if (ui->departmentTabs->currentWidget() == ui->respiratoryTab) {
        currentTable = ui->respiratoryTable;
        currentDept = &::respiratoryDept;
    } else if (ui->departmentTabs->currentWidget() == ui->generalTab) {
        currentTable = ui->generalTable;
        currentDept = &::generalDept;
    }
    
    if (!currentTable || !currentTable->currentItem()) {
        QMessageBox::warning(this, "Error", "Please select a patient to update.");
        return;
    }
    
    int patientId = currentTable->item(currentTable->currentRow(), 0)->text().toInt();
    int currentPriority = currentTable->item(currentTable->currentRow(), 2)->text().toInt();
    
    bool ok;
    int newPriority = QInputDialog::getInt(this, "Update Priority",
                                         "Enter new priority (1-10):",
                                         currentPriority, 1, 10, 1, &ok);
    
    if (ok) {
        currentDept->updatePatientPriority(patientId, newPriority);
        updateQueues();
    }
}

void NurseInterface::on_changeDepartmentButton_clicked()
{
    QTableWidget* currentTable = nullptr;
    Department* sourceDept = nullptr;
    
    // Determine which tab is active
    if (ui->departmentTabs->currentWidget() == ui->cardiacTab) {
        currentTable = ui->cardiacTable;
        sourceDept = &cardiacDept;
    } else if (ui->departmentTabs->currentWidget() == ui->respiratoryTab) {
        currentTable = ui->respiratoryTable;
        sourceDept = &respiratoryDept;
    } else if (ui->departmentTabs->currentWidget() == ui->generalTab) {
        currentTable = ui->generalTable;
        sourceDept = &generalDept;
    }
    
    if (!currentTable || !currentTable->currentItem()) {
        QMessageBox::warning(this, "Error", "Please select a patient to transfer.");
        return;
    }
    
    int patientId = currentTable->item(currentTable->currentRow(), 0)->text().toInt();
    
    QStringList departments;
    departments << "Cardiac" << "Respiratory" << "General";
    departments.removeOne(sourceDept->getName().c_str());
    
    bool ok;
    QString newDept = QInputDialog::getItem(this, "Change Department",
                                          "Select new department:",
                                          departments, 0, false, &ok);
    
    if (ok && !newDept.isEmpty()) {
        Department* targetDept = nullptr;
        if (newDept == "Cardiac") targetDept = &cardiacDept;
        else if (newDept == "Respiratory") targetDept = &respiratoryDept;
        else if (newDept == "General") targetDept = &generalDept;
        
        if (targetDept) {
            sourceDept->transferPatient(patientId, *targetDept);
            updateQueues();
        }
    }
}

void NurseInterface::on_refreshButton_clicked()
{
    // Simply refresh the queues
    updateQueues();

    // Update the last refresh time
    ui->lastRefreshLabel->setText("Last Updated: " +
                                  QDateTime::currentDateTime().toString("hh:mm:ss AP"));
}

void NurseInterface::on_logoutButton_clicked()
{
    if (QMessageBox::question(this, "Logout", "Are you sure you want to logout?",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        // Get the parent (NurseLogin dialog)
        QWidget* loginDialog = this->parentWidget();

        // Get the main window (grandparent)
        QWidget* mainWindow = nullptr;
        if (loginDialog) {
            mainWindow = loginDialog->parentWidget();
        }

        // Show the main window if found
        if (mainWindow) {
            mainWindow->show();
        }

        // Close this window (will delete when closed)
        this->close();

        // Also close the login dialog
        if (loginDialog) {
            loginDialog->close();
        }
    }
}

/*QString NurseInterface::calculateWaitTime(const QDateTime& entryTime)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    qint64 secs = entryTime.secsTo(currentTime);
    
    int hours = secs / 3600;
    int minutes = (secs % 3600) / 60;
    
    if (hours > 0) {
        return QString("%1h %2m").arg(hours).arg(minutes);
    } else {
        return QString("%1m").arg(minutes);
    }
}*/

QString NurseInterface::calculateWaitTime(const QDateTime& entryTime)
{
    QDateTime currentTime = QDateTime::currentDateTime();
    qint64 secs = entryTime.secsTo(currentTime);

    int hours = secs / 3600;
    int minutes = (secs % 3600) / 60;

    if (hours > 0) {
        return QString("%1h %2m").arg(hours).arg(minutes);
    } else {
        return QString("%1m").arg(minutes);
    }
}

void NurseInterface::updateQueues()
{
    updateDepartmentView(::cardiacDept, ui->cardiacTable);
    updateDepartmentView(::respiratoryDept, ui->respiratoryTable);
    updateDepartmentView(::generalDept, ui->generalTable);
    
    // Update last refresh time
    ui->lastRefreshLabel->setText("Last Updated: " + 
                                QDateTime::currentDateTime().toString("hh:mm:ss AP"));
}

// Helper method to find patient
Patient* NurseInterface::findPatient(int patientId)
{
    // Leverage the PatientDatabase singleton to retrieve the patient by ID.
    Patient* p = PatientDatabase::instance().findPatient(patientId);

    // Optional: Add debug output to see if we found the patient or not
    if (!p) {
        qDebug() << "NurseInterface::findPatient - No patient found with ID:" << patientId;
    } else {
        qDebug() << "NurseInterface::findPatient - Found patient with ID:" << patientId
                 << "Name:" << QString::fromStdString(p->getName());
    }

    return p;
    //return nullptr;
}

// Add a helper function for recording vitals:
void NurseInterface::recordPatientVitals(int patientId)
{
    Patient* patient = findPatient(patientId);
    if (!patient) {
        QMessageBox::warning(this, "Error", "Patient not found.");
        return;
    }

    // Open the vitals dialog
    VitalsDialog dialog(patient, this);
    dialog.setWindowTitle("Record Vitals - " + QString::fromStdString(patient->getName()));

    // If the dialog is accepted (Save button clicked), refresh the queue
    if (dialog.exec() == QDialog::Accepted) {
        updateQueues();
    }
}

// Add a new button handler for recording vitals:
void NurseInterface::on_recordVitalsButton_clicked()
{
    QTableWidget* currentTable = nullptr;

    // Determine which tab is active
    if (ui->departmentTabs->currentWidget() == ui->cardiacTab) {
        currentTable = ui->cardiacTable;
    } else if (ui->departmentTabs->currentWidget() == ui->respiratoryTab) {
        currentTable = ui->respiratoryTable;
    } else if (ui->departmentTabs->currentWidget() == ui->generalTab) {
        currentTable = ui->generalTable;
    }

    if (!currentTable || !currentTable->currentItem()) {
        QMessageBox::warning(this, "Error", "Please select a patient to record vitals.");
        return;
    }

    int patientId = currentTable->item(currentTable->currentRow(), 0)->text().toInt();
    recordPatientVitals(patientId);
}

// In nurseinterface.cpp, add the implementation:
void NurseInterface::on_editSymptomsButton_clicked()
{
    QTableWidget* currentTable = nullptr;
    Department* currentDept = nullptr;

    // Determine which tab is active
    if (ui->departmentTabs->currentWidget() == ui->cardiacTab) {
        currentTable = ui->cardiacTable;
        currentDept = &cardiacDept;
    } else if (ui->departmentTabs->currentWidget() == ui->respiratoryTab) {
        currentTable = ui->respiratoryTable;
        currentDept = &respiratoryDept;
    } else if (ui->departmentTabs->currentWidget() == ui->generalTab) {
        currentTable = ui->generalTable;
        currentDept = &generalDept;
    }

    if (!currentTable || !currentTable->currentItem()) {
        QMessageBox::warning(this, "Error", "Please select a patient to edit symptoms.");
        return;
    }

    int patientId = currentTable->item(currentTable->currentRow(), 0)->text().toInt();
    Patient* patient = findPatient(patientId);

    if (!patient) {
        QMessageBox::warning(this, "Error", "Patient not found.");
        return;
    }

    EditSymptomsDialog dialog(patient, currentDept, this);
    if (dialog.exec() == QDialog::Accepted) {
        updateQueues();
    }
}
