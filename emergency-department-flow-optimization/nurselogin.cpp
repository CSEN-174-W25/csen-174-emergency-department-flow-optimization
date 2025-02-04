#include "nurselogin.h"
#include "ui_nurselogin.h"
#include <QMessageBox>

NurseLogin::NurseLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NurseLogin),
    nurseInterface(nullptr)
{
    ui->setupUi(this);
    this->setWindowTitle("Nurse Login");
}

NurseLogin::~NurseLogin()
{
    delete ui;
}

void NurseLogin::on_loginButton_clicked()
{
    QString username = ui->usernameInput->text();
    QString password = ui->passwordInput->text();
    
    if (validateCredentials(username, password)) {
        if (!nurseInterface) {
            nurseInterface = new NurseInterface(this);
        }
        nurseInterface->show();
        this->hide();
    } else {
        QMessageBox::warning(this, "Login Failed", 
                           "Invalid username or password.");
    }
}

void NurseLogin::on_cancelButton_clicked()
{
    this->parentWidget()->show();
    this->hide();
}

bool NurseLogin::validateCredentials(const QString& username, const QString& password)
{
    // Test credentials as specified
    return (username == "nurse" && password == "password");
}