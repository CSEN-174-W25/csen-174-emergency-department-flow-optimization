// vitals_dialog.h
#ifndef VITALS_DIALOG_H
#define VITALS_DIALOG_H

#include <QDialog>
#include "patient.h"

namespace Ui {
class VitalsDialog;
}

class VitalsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VitalsDialog(Patient* patient, QWidget *parent = nullptr);
    ~VitalsDialog();

private slots:
    void on_saveButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::VitalsDialog *ui;
    Patient* _patient;

    void loadPatientVitals();
};

#endif // VITALS_DIALOG_H
