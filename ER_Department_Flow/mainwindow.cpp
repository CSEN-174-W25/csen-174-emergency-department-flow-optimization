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
    PatientForm *newForm = new PatientForm(this); // Parent is main window
    newForm->setWindowFlags(Qt::Window);          // Make it a top-level window
    newForm->show();
    newForm->activateWindow();                    // Bring it to the front
    newForm->raise();                             // Raise above other windows
    this->hide();
}

void MainWindow::on_nurseButton_clicked()
{
    /*if (!nurseLogin) {
        nurseLogin = new NurseLogin(this);
    }
    nurseLogin->show();
    this->hide();*/
    NurseLogin *newForm = new NurseLogin(this);
    newForm->setWindowFlags(Qt::Window);
    newForm->show();
    newForm->activateWindow();
    newForm->raise();
    this->hide();
}
