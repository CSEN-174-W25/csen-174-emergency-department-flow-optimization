/********************************************************************************
** Form generated from reading UI file 'nurseinterface.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NURSEINTERFACE_H
#define UI_NURSEINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NurseInterface
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *welcomeLabel;
    QTabWidget *departmentTabs;
    QWidget *cardiacTab;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *cardiacTable;
    QWidget *respiratoryTab;
    QVBoxLayout *verticalLayout_3;
    QTableWidget *respiratoryTable;
    QWidget *generalTab;
    QVBoxLayout *verticalLayout_4;
    QTableWidget *generalTable;
    QHBoxLayout *horizontalLayout;
    QPushButton *viewPatientButton;
    QPushButton *updatePriorityButton;
    QPushButton *changeDepartmentButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *refreshButton;
    QPushButton *logoutButton;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lastRefreshLabel;
    QSpacerItem *horizontalSpacer_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *NurseInterface)
    {
        if (NurseInterface->objectName().isEmpty())
            NurseInterface->setObjectName("NurseInterface");
        NurseInterface->resize(1024, 768);
        centralwidget = new QWidget(NurseInterface);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        welcomeLabel = new QLabel(centralwidget);
        welcomeLabel->setObjectName("welcomeLabel");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        welcomeLabel->setFont(font);
        welcomeLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(welcomeLabel);

        departmentTabs = new QTabWidget(centralwidget);
        departmentTabs->setObjectName("departmentTabs");
        cardiacTab = new QWidget();
        cardiacTab->setObjectName("cardiacTab");
        verticalLayout_2 = new QVBoxLayout(cardiacTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        cardiacTable = new QTableWidget(cardiacTab);
        cardiacTable->setObjectName("cardiacTable");
        cardiacTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        cardiacTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout_2->addWidget(cardiacTable);

        departmentTabs->addTab(cardiacTab, QString());
        respiratoryTab = new QWidget();
        respiratoryTab->setObjectName("respiratoryTab");
        verticalLayout_3 = new QVBoxLayout(respiratoryTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        respiratoryTable = new QTableWidget(respiratoryTab);
        respiratoryTable->setObjectName("respiratoryTable");
        respiratoryTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        respiratoryTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout_3->addWidget(respiratoryTable);

        departmentTabs->addTab(respiratoryTab, QString());
        generalTab = new QWidget();
        generalTab->setObjectName("generalTab");
        verticalLayout_4 = new QVBoxLayout(generalTab);
        verticalLayout_4->setObjectName("verticalLayout_4");
        generalTable = new QTableWidget(generalTab);
        generalTable->setObjectName("generalTable");
        generalTable->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        generalTable->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout_4->addWidget(generalTable);

        departmentTabs->addTab(generalTab, QString());

        verticalLayout->addWidget(departmentTabs);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        viewPatientButton = new QPushButton(centralwidget);
        viewPatientButton->setObjectName("viewPatientButton");
        viewPatientButton->setMinimumSize(QSize(150, 30));

        horizontalLayout->addWidget(viewPatientButton);

        updatePriorityButton = new QPushButton(centralwidget);
        updatePriorityButton->setObjectName("updatePriorityButton");
        updatePriorityButton->setMinimumSize(QSize(150, 30));

        horizontalLayout->addWidget(updatePriorityButton);

        changeDepartmentButton = new QPushButton(centralwidget);
        changeDepartmentButton->setObjectName("changeDepartmentButton");
        changeDepartmentButton->setMinimumSize(QSize(150, 30));

        horizontalLayout->addWidget(changeDepartmentButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        refreshButton = new QPushButton(centralwidget);
        refreshButton->setObjectName("refreshButton");
        refreshButton->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(refreshButton);

        logoutButton = new QPushButton(centralwidget);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setMinimumSize(QSize(100, 30));

        horizontalLayout->addWidget(logoutButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        lastRefreshLabel = new QLabel(centralwidget);
        lastRefreshLabel->setObjectName("lastRefreshLabel");

        horizontalLayout_2->addWidget(lastRefreshLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        NurseInterface->setCentralWidget(centralwidget);
        menubar = new QMenuBar(NurseInterface);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1024, 21));
        NurseInterface->setMenuBar(menubar);
        statusbar = new QStatusBar(NurseInterface);
        statusbar->setObjectName("statusbar");
        NurseInterface->setStatusBar(statusbar);

        retranslateUi(NurseInterface);

        departmentTabs->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(NurseInterface);
    } // setupUi

    void retranslateUi(QMainWindow *NurseInterface)
    {
        NurseInterface->setWindowTitle(QCoreApplication::translate("NurseInterface", "Nurse Interface", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("NurseInterface", "Emergency Department Queue Management", nullptr));
        departmentTabs->setTabText(departmentTabs->indexOf(cardiacTab), QCoreApplication::translate("NurseInterface", "Cardiac Department", nullptr));
        departmentTabs->setTabText(departmentTabs->indexOf(respiratoryTab), QCoreApplication::translate("NurseInterface", "Respiratory Department", nullptr));
        departmentTabs->setTabText(departmentTabs->indexOf(generalTab), QCoreApplication::translate("NurseInterface", "General Department", nullptr));
        viewPatientButton->setText(QCoreApplication::translate("NurseInterface", "View Patient Details", nullptr));
        updatePriorityButton->setText(QCoreApplication::translate("NurseInterface", "Update Priority", nullptr));
        changeDepartmentButton->setText(QCoreApplication::translate("NurseInterface", "Change Department", nullptr));
        refreshButton->setText(QCoreApplication::translate("NurseInterface", "Refresh", nullptr));
        logoutButton->setText(QCoreApplication::translate("NurseInterface", "Logout", nullptr));
        lastRefreshLabel->setText(QCoreApplication::translate("NurseInterface", "Last Updated: ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NurseInterface: public Ui_NurseInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NURSEINTERFACE_H
