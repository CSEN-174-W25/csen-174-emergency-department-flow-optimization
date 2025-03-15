// vitals_dialog.cpp
#include "vitals_dialog.h"
#include "ui_vitals_dialog.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

VitalsDialog::VitalsDialog(Patient* patient, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VitalsDialog),
    _patient(patient)
{
    ui->setupUi(this);
    this->setWindowTitle("Record Patient Vitals");

    // Set up validators
    // Heart rate (40-200 bpm)
    ui->heartRateInput->setValidator(new QIntValidator(40, 200, this));

    // Blood pressure (format: 120/80)
    QRegularExpression bpRegex("^\\d{2,3}\\/\\d{2,3}$");
    ui->bloodPressureInput->setValidator(new QRegularExpressionValidator(bpRegex, this));

    // Blood sugar (40-500 mg/dL)
    ui->bloodSugarInput->setValidator(new QIntValidator(40, 500, this));

    // Temperature (95.0-108.0 Fahrenheit)
    ui->temperatureInput->setValidator(new QDoubleValidator(95.0, 108.0, 1, this));

    // Blood oxygen (70-100%)
    ui->oxygenInput->setValidator(new QIntValidator(70, 100, this));

    // Load existing vitals if available
    loadPatientVitals();
}

VitalsDialog::~VitalsDialog()
{
    delete ui;
}

void VitalsDialog::loadPatientVitals()
{
    if (_patient && _patient->hasVitalsRecorded()) {
        ui->heartRateInput->setText(QString::number(_patient->getHeartRate()));
        ui->bloodPressureInput->setText(QString::fromStdString(_patient->getBloodPressure()));
        ui->bloodSugarInput->setText(QString::number(_patient->getBloodSugar()));
        ui->temperatureInput->setText(QString::number(_patient->getBodyTemperature(), 'f', 1));
        ui->oxygenInput->setText(QString::number(_patient->getBloodOxygen()));
    }
}

void VitalsDialog::on_saveButton_clicked()
{
    // Validate inputs
    if (ui->heartRateInput->text().isEmpty() ||
        ui->bloodPressureInput->text().isEmpty() ||
        ui->bloodSugarInput->text().isEmpty() ||
        ui->temperatureInput->text().isEmpty() ||
        ui->oxygenInput->text().isEmpty()) {

        QMessageBox::warning(this, "Incomplete Data", "Please fill in all vital sign fields.");
        return;
    }

    // Save vitals to patient
    _patient->setHeartRate(ui->heartRateInput->text().toInt());
    _patient->setBloodPressure(ui->bloodPressureInput->text().toStdString());
    _patient->setBloodSugar(ui->bloodSugarInput->text().toInt());
    _patient->setBodyTemperature(ui->temperatureInput->text().toFloat());
    _patient->setBloodOxygen(ui->oxygenInput->text().toInt());
    _patient->setVitalsRecorded(true);

    QMessageBox::information(this, "Success", "Vital signs recorded successfully.");
    accept();
}

void VitalsDialog::on_cancelButton_clicked()
{
    reject();
}
