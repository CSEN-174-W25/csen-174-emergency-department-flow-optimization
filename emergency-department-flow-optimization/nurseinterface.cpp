#include "nurseinterface.h"
#include "ui_nurseinterface.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDateTime>

NurseInterface::NurseInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NurseInterface),
    cardiacDept("Cardiac"),
    respiratoryDept("Respiratory"),
    generalDept("General")
{
    ui->setupUi(this);
    this->setWindowTitle("Nurse Interface");
    
    // Setup refresh timer
    refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, &NurseInterface::updateQueues);
    refreshTimer->start(30000);  // Refresh every 30 seconds
    
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
    headers << "Patient ID" << "Name" << "Priority" << "Wait Time" << "Symptoms";
    
    // Cardiac Department Table
    ui->cardiacTable->setColumnCount(5);
    ui->cardiacTable->setHorizontalHeaderLabels(headers);
    ui->cardiacTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->cardiacTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->cardiacTable->setSelectionMode(QAbstractItemView::SingleSelection);
    
    // Respiratory Department Table
    ui->respiratoryTable->setColumnCount(5);
    ui->respiratoryTable->setHorizontalHeaderLabels(headers);
    ui->respiratoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->respiratoryTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->respiratoryTable->setSelectionMode(QAbstractItemView::SingleSelection);
    
    // General Department Table
    ui->generalTable->setColumnCount(5);
    ui->generalTable->setHorizontalHeaderLabels(headers);
    ui->generalTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->generalTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->generalTable->setSelectionMode(QAbstractItemView::SingleSelection);
}

void NurseInterface::updateDepartmentView(const Department& dept, QTableWidget* table)
{
    table->setRowCount(0);  // Clear existing rows
    
    auto queue = dept.getQueue();
    for (const auto& entry : queue) {
        int row = table->rowCount();
        table->insertRow(row);
        
        // Get patient information
        Patient* patient = findPatient(entry.patientId);  // You'll need to implement this
        if (!patient) continue;
        
        // Calculate wait time
        QDateTime entryTime = QDateTime::fromSecsSinceEpoch(entry.entryTime);
        QString waitTime = calculateWaitTime(entryTime);
        
        // Add patient information to table
        table->setItem(row, 0, new QTableWidgetItem(QString::number(entry.patientId)));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(patient->getName())));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(entry.priority)));
        table->setItem(row, 3, new QTableWidgetItem(waitTime));
        
        // Create symptoms string
        QString symptomsStr;
        for (const auto& symptom : patient->getSymptoms().getSymptoms()) {
            if (!symptomsStr.isEmpty()) symptomsStr += ", ";
            symptomsStr += QString::fromStdString(symptom.symptomId);
        }
        table->setItem(row, 4, new QTableWidgetItem(symptomsStr));
        
        // Color code based on priority
        if (entry.priority >= 8) {
            // High priority - red background
            for (int col = 0; col < table->columnCount(); ++col) {
                table->item(row, col)->setBackground(QColor(255, 200, 200));
            }
        }
        else if (entry.priority >= 5) {
            // Medium priority - yellow background
            for (int col = 0; col < table->columnCount(); ++col) {
                table->item(row, col)->setBackground(QColor(255, 255, 200));
            }
        }
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
    Patient* patient = nullptr;//= findPatient(patientId);
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
                            "Member ID: %8\n\n"
                            "Medical History: %9\n\n"
                            "Current Medications: %10\n"
                            "Allergies: %11")
                             .arg(QString::fromStdString(patient->getName()))
                             .arg(patient->getPatientId())
                             .arg(QString::fromStdString(patient->getGender()))
                             .arg(patient->getDOB().toString("MM/dd/yyyy"))
                             .arg(QString::fromStdString(patient->getContact()))
                             .arg(QString::fromStdString(patient->getEmergencyContact()))
                             .arg(QString::fromStdString(patient->getInsuranceProvider()))
                             .arg(QString::fromStdString(patient->getInsuranceMemberId()))
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
        currentDept = &cardiacDept;
    } else if (ui->departmentTabs->currentWidget() == ui->respiratoryTab) {
        currentTable = ui->respiratoryTable;
        currentDept = &respiratoryDept;
    } else if (ui->departmentTabs->currentWidget() == ui->generalTab) {
        currentTable = ui->generalTable;
        currentDept = &generalDept;
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
    updateQueues();
}

void NurseInterface::on_logoutButton_clicked()
{
    if (QMessageBox::question(this, "Logout", "Are you sure you want to logout?",
                            QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
        this->parentWidget()->show();
        this->hide();
    }
}

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
    updateDepartmentView(cardiacDept, ui->cardiacTable);
    updateDepartmentView(respiratoryDept, ui->respiratoryTable);
    updateDepartmentView(generalDept, ui->generalTable);
    
    // Update last refresh time
    ui->lastRefreshLabel->setText("Last Updated: " + 
                                QDateTime::currentDateTime().toString("hh:mm:ss AP"));
}

// Helper method to find patient - you'll need to implement this based on your storage system
Patient* NurseInterface::findPatient(int patientId)
{
    // This is a placeholder - implement based on your patient storage system
    // You might want to use a database or some other persistent storage
    return nullptr;
}
