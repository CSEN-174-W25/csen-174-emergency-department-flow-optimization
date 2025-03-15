#ifndef EDIT_SYMPTOMS_DIALOG_H
#define EDIT_SYMPTOMS_DIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QSpinBox>
#include "patient.h"
#include "department.h"

namespace Ui {
class EditSymptomsDialog;
}

class EditSymptomsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditSymptomsDialog(Patient* patient, Department* currentDept, QWidget *parent = nullptr);
    ~EditSymptomsDialog();

private slots:
    void on_addSymptomButton_clicked();
    void on_removeSymptomButton_clicked();
    void on_saveButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::EditSymptomsDialog *ui;
    Patient* _patient;
    Department* _currentDept;
    void updateSymptomList();
    void updateAvailableSymptoms();
};

#endif
