#ifndef NURSEINTERFACE_H
#define NURSEINTERFACE_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTimer>
#include <QInputDialog>
#include "department.h"
#include "patient.h"

namespace Ui {
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
    
    // Auto-refresh timer slot
    QString calculateWaitTime(const QDateTime& entryTime);
    void updateQueues();
    Patient* findPatient(int patientId);

private:
    Ui::NurseInterface *ui;
    QTimer *refreshTimer;
    
    // Department queues
    Department cardiacDept;
    Department respiratoryDept;
    Department generalDept;
    
    void setupDepartmentViews();
    void updateDepartmentView(const Department& dept, QTableWidget* table);
    void viewPatientDetails(int patientId);
    bool changeDepartment(int patientId, DepartmentType newDept);
    void updatePatientPriority(int patientId, int newPriority);
};

#endif
