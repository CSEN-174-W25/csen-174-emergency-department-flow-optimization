#ifndef NURSELOGIN_H
#define NURSELOGIN_H

#include <QDialog>
#include "nurseinterface.h"

namespace Ui {
    class NurseLogin;
}

class NurseLogin : public QDialog
{
    Q_OBJECT

    public:
        explicit NurseLogin(QWidget *parent = nullptr);
        ~NurseLogin();

    private slots:
        void on_loginButton_clicked();
        void on_cancelButton_clicked();

    private:
        Ui::NurseLogin *ui;
        NurseInterface *nurseInterface;

        bool validateCredentials(const QString& username, const QString& password);
};

#endif
