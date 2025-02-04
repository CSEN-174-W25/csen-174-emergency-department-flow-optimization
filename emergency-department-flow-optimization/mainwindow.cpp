#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Emergency Department System");
    
    // Initialize forms
    patientForm = nullptr;
    nurseLogin = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_patientButton_clicked()
{
    if (!patientForm) {
        patientForm = new PatientForm(this);
    }
    patientForm->show();
    this->hide();
}

void MainWindow::on_nurseButton_clicked()
{
    if (!nurseLogin) {
        nurseLogin = new NurseLogin(this);
    }
    nurseLogin->show();
    this->hide();
}