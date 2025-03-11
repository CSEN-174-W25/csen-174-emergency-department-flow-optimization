#ifndef NURSEINTERFACE_H
#define NURSEINTERFACE_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTimer>
#include <QInputDialog>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QColor>
#include "department.h"
#include "patient.h"
#include "edit_symptoms_dialog.h"

namespace Ui {
class PriorityTableItem : public QTableWidgetItem {
public:
    PriorityTableItem(int priority) : QTableWidgetItem(QString::number(priority)) {
        setData(Qt::DisplayRole, priority);
    }

    // Override the < operator for proper sorting
    bool operator<(const QTableWidgetItem &other) const override {
        // Lower priority number = higher priority, so reverse the comparison
        return data(Qt::DisplayRole).toInt() < other.data(Qt::DisplayRole).toInt();
    }
};

class NurseInterface;
}

class NurseInterface : public QMainWindow
{
    Q_OBJECT

public:
    explicit NurseInterface(QWidget *parent = nullptr);
    ~NurseInterface();

private slots:
    void on_logoutButton_clicked();
    void on_viewPatientButton_clicked();
    void on_updatePriorityButton_clicked();
    void on_changeDepartmentButton_clicked();
    void on_refreshButton_clicked();
    void on_recordVitalsButton_clicked();
    void on_editSymptomsButton_clicked();
    void on_dischargePatientButton_clicked();

    // Auto-refresh timer slot
    void updateQueues();

private:
    Ui::NurseInterface *ui;
    QTimer *refreshTimer;

    void setupDepartmentViews();
    void updateDepartmentView(const Department& dept, QTableWidget* table);
    void viewPatientDetails(int patientId);
    bool changeDepartment(int patientId, DepartmentType newDept);
    void updatePatientPriority(int patientId, int newPriority);

    Patient* findPatient(int patientId);
    QString calculateWaitTime(const QDateTime& entryTime);

    void recordPatientVitals(int patientId);

    void setupDischargeView();
    void updateDischargeView();
    void addPatientsToDischargeTable(const std::vector<Department::QueueEntry>& patients, const QString& deptName);
    void dischargePatient(int patientId);
};
#endif
