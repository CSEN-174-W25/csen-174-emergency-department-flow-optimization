#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "patientform.h"
#include "nurselogin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_patientButton_clicked();
    void on_nurseButton_clicked();

private:
    Ui::MainWindow *ui;
    PatientForm *patientForm;
    NurseLogin *nurseLogin;
};

#endif
