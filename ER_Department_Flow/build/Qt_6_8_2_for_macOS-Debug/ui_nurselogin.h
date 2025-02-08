/********************************************************************************
** Form generated from reading UI file 'nurselogin.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NURSELOGIN_H
#define UI_NURSELOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NurseLogin
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *titleLabel;
    QFormLayout *formLayout;
    QLabel *usernameLabel;
    QLineEdit *usernameInput;
    QLabel *passwordLabel;
    QLineEdit *passwordInput;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *loginButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *NurseLogin)
    {
        if (NurseLogin->objectName().isEmpty())
            NurseLogin->setObjectName("NurseLogin");
        NurseLogin->resize(400, 300);
        verticalLayout = new QVBoxLayout(NurseLogin);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        titleLabel = new QLabel(NurseLogin);
        titleLabel->setObjectName("titleLabel");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout->setFormAlignment(Qt::AlignHCenter|Qt::AlignTop);
        formLayout->setHorizontalSpacing(20);
        formLayout->setVerticalSpacing(15);
        formLayout->setContentsMargins(40, -1, 40, -1);
        usernameLabel = new QLabel(NurseLogin);
        usernameLabel->setObjectName("usernameLabel");
        QFont font1;
        font1.setPointSize(10);
        usernameLabel->setFont(font1);

        formLayout->setWidget(0, QFormLayout::LabelRole, usernameLabel);

        usernameInput = new QLineEdit(NurseLogin);
        usernameInput->setObjectName("usernameInput");
        usernameInput->setMinimumSize(QSize(200, 25));

        formLayout->setWidget(0, QFormLayout::FieldRole, usernameInput);

        passwordLabel = new QLabel(NurseLogin);
        passwordLabel->setObjectName("passwordLabel");
        passwordLabel->setFont(font1);

        formLayout->setWidget(1, QFormLayout::LabelRole, passwordLabel);

        passwordInput = new QLineEdit(NurseLogin);
        passwordInput->setObjectName("passwordInput");
        passwordInput->setMinimumSize(QSize(200, 25));
        passwordInput->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, passwordInput);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        loginButton = new QPushButton(NurseLogin);
        loginButton->setObjectName("loginButton");
        loginButton->setMinimumSize(QSize(100, 30));
        loginButton->setFont(font1);

        horizontalLayout->addWidget(loginButton);

        cancelButton = new QPushButton(NurseLogin);
        cancelButton->setObjectName("cancelButton");
        cancelButton->setMinimumSize(QSize(100, 30));
        cancelButton->setFont(font1);

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        retranslateUi(NurseLogin);

        QMetaObject::connectSlotsByName(NurseLogin);
    } // setupUi

    void retranslateUi(QDialog *NurseLogin)
    {
        NurseLogin->setWindowTitle(QCoreApplication::translate("NurseLogin", "Nurse Login", nullptr));
        titleLabel->setText(QCoreApplication::translate("NurseLogin", "Nurse Login", nullptr));
        usernameLabel->setText(QCoreApplication::translate("NurseLogin", "Username:", nullptr));
        passwordLabel->setText(QCoreApplication::translate("NurseLogin", "Password:", nullptr));
        loginButton->setText(QCoreApplication::translate("NurseLogin", "Login", nullptr));
        cancelButton->setText(QCoreApplication::translate("NurseLogin", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NurseLogin: public Ui_NurseLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NURSELOGIN_H
