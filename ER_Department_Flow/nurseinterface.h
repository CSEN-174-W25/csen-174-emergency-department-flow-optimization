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
};
#endif
