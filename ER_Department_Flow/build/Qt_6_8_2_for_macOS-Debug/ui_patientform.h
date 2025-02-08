/********************************************************************************
** Form generated from reading UI file 'patientform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTFORM_H
#define UI_PATIENTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PatientForm
{
public:
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *personalInfoPage;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QFormLayout *formLayout;
    QLabel *nameLabel;
    QLineEdit *nameLineEdit;
    QLabel *dobLabel;
    QDateEdit *dobDateEdit;
    QLabel *genderLabel;
    QComboBox *genderComboBox;
    QLabel *contactLabel;
    QLineEdit *contactLineEdit;
    QLabel *emergencyContactLabel;
    QLineEdit *emergencyContactLineEdit;
    QLabel *addressLabel;
    QTextEdit *addressTextEdit;
    QWidget *insurancePage;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QRadioButton *hasInsuranceRadio;
    QGroupBox *insuranceGroupBox;
    QFormLayout *formLayout_2;
    QLabel *providerLabel;
    QLineEdit *providerLineEdit;
    QLabel *memberIdLabel;
    QLineEdit *memberIdLineEdit;
    QWidget *symptomsPage;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *availableSymptomsLabel;
    QListWidget *symptomList;
    QHBoxLayout *horizontalLayout_3;
    QLabel *severityLabel;
    QSpinBox *severitySpinBox;
    QPushButton *addSymptomButton;
    QVBoxLayout *verticalLayout_6;
    QLabel *selectedSymptomsLabel;
    QListWidget *selectedSymptomList;
    QPushButton *removeSymptomButton;
    QWidget *medicalHistoryPage;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_4;
    QLabel *medicalHistoryLabel;
    QTextEdit *medicalHistoryTextEdit;
    QLabel *familyHistoryLabel;
    QTextEdit *familyHistoryTextEdit;
    QLabel *medicationsLabel;
    QTextEdit *medicationsTextEdit;
    QCheckBox *allergiesCheckBox;
    QTextEdit *allergiesTextEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelButton;
    QPushButton *backButton;
    QPushButton *nextButton;

    void setupUi(QWidget *PatientForm)
    {
        if (PatientForm->objectName().isEmpty())
            PatientForm->setObjectName("PatientForm");
        PatientForm->resize(800, 600);
        verticalLayout = new QVBoxLayout(PatientForm);
        verticalLayout->setObjectName("verticalLayout");
        stackedWidget = new QStackedWidget(PatientForm);
        stackedWidget->setObjectName("stackedWidget");
        personalInfoPage = new QWidget();
        personalInfoPage->setObjectName("personalInfoPage");
        verticalLayout_2 = new QVBoxLayout(personalInfoPage);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(personalInfoPage);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);

        verticalLayout_2->addWidget(label);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        nameLabel = new QLabel(personalInfoPage);
        nameLabel->setObjectName("nameLabel");

        formLayout->setWidget(0, QFormLayout::LabelRole, nameLabel);

        nameLineEdit = new QLineEdit(personalInfoPage);
        nameLineEdit->setObjectName("nameLineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, nameLineEdit);

        dobLabel = new QLabel(personalInfoPage);
        dobLabel->setObjectName("dobLabel");

        formLayout->setWidget(1, QFormLayout::LabelRole, dobLabel);

        dobDateEdit = new QDateEdit(personalInfoPage);
        dobDateEdit->setObjectName("dobDateEdit");

        formLayout->setWidget(1, QFormLayout::FieldRole, dobDateEdit);

        genderLabel = new QLabel(personalInfoPage);
        genderLabel->setObjectName("genderLabel");

        formLayout->setWidget(2, QFormLayout::LabelRole, genderLabel);

        genderComboBox = new QComboBox(personalInfoPage);
        genderComboBox->setObjectName("genderComboBox");

        formLayout->setWidget(2, QFormLayout::FieldRole, genderComboBox);

        contactLabel = new QLabel(personalInfoPage);
        contactLabel->setObjectName("contactLabel");

        formLayout->setWidget(3, QFormLayout::LabelRole, contactLabel);

        contactLineEdit = new QLineEdit(personalInfoPage);
        contactLineEdit->setObjectName("contactLineEdit");

        formLayout->setWidget(3, QFormLayout::FieldRole, contactLineEdit);

        emergencyContactLabel = new QLabel(personalInfoPage);
        emergencyContactLabel->setObjectName("emergencyContactLabel");

        formLayout->setWidget(4, QFormLayout::LabelRole, emergencyContactLabel);

        emergencyContactLineEdit = new QLineEdit(personalInfoPage);
        emergencyContactLineEdit->setObjectName("emergencyContactLineEdit");

        formLayout->setWidget(4, QFormLayout::FieldRole, emergencyContactLineEdit);

        addressLabel = new QLabel(personalInfoPage);
        addressLabel->setObjectName("addressLabel");

        formLayout->setWidget(5, QFormLayout::LabelRole, addressLabel);

        addressTextEdit = new QTextEdit(personalInfoPage);
        addressTextEdit->setObjectName("addressTextEdit");
        addressTextEdit->setMaximumSize(QSize(16777215, 100));

        formLayout->setWidget(5, QFormLayout::FieldRole, addressTextEdit);


        verticalLayout_2->addLayout(formLayout);

        stackedWidget->addWidget(personalInfoPage);
        insurancePage = new QWidget();
        insurancePage->setObjectName("insurancePage");
        verticalLayout_3 = new QVBoxLayout(insurancePage);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(insurancePage);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        verticalLayout_3->addWidget(label_2);

        hasInsuranceRadio = new QRadioButton(insurancePage);
        hasInsuranceRadio->setObjectName("hasInsuranceRadio");

        verticalLayout_3->addWidget(hasInsuranceRadio);

        insuranceGroupBox = new QGroupBox(insurancePage);
        insuranceGroupBox->setObjectName("insuranceGroupBox");
        formLayout_2 = new QFormLayout(insuranceGroupBox);
        formLayout_2->setObjectName("formLayout_2");
        providerLabel = new QLabel(insuranceGroupBox);
        providerLabel->setObjectName("providerLabel");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, providerLabel);

        providerLineEdit = new QLineEdit(insuranceGroupBox);
        providerLineEdit->setObjectName("providerLineEdit");

        formLayout_2->setWidget(0, QFormLayout::FieldRole, providerLineEdit);

        memberIdLabel = new QLabel(insuranceGroupBox);
        memberIdLabel->setObjectName("memberIdLabel");

        formLayout_2->setWidget(1, QFormLayout::LabelRole, memberIdLabel);

        memberIdLineEdit = new QLineEdit(insuranceGroupBox);
        memberIdLineEdit->setObjectName("memberIdLineEdit");

        formLayout_2->setWidget(1, QFormLayout::FieldRole, memberIdLineEdit);


        verticalLayout_3->addWidget(insuranceGroupBox);

        stackedWidget->addWidget(insurancePage);
        symptomsPage = new QWidget();
        symptomsPage->setObjectName("symptomsPage");
        verticalLayout_4 = new QVBoxLayout(symptomsPage);
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_3 = new QLabel(symptomsPage);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        verticalLayout_4->addWidget(label_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        availableSymptomsLabel = new QLabel(symptomsPage);
        availableSymptomsLabel->setObjectName("availableSymptomsLabel");

        verticalLayout_5->addWidget(availableSymptomsLabel);

        symptomList = new QListWidget(symptomsPage);
        symptomList->setObjectName("symptomList");

        verticalLayout_5->addWidget(symptomList);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        severityLabel = new QLabel(symptomsPage);
        severityLabel->setObjectName("severityLabel");

        horizontalLayout_3->addWidget(severityLabel);

        severitySpinBox = new QSpinBox(symptomsPage);
        severitySpinBox->setObjectName("severitySpinBox");

        horizontalLayout_3->addWidget(severitySpinBox);

        addSymptomButton = new QPushButton(symptomsPage);
        addSymptomButton->setObjectName("addSymptomButton");

        horizontalLayout_3->addWidget(addSymptomButton);


        verticalLayout_5->addLayout(horizontalLayout_3);


        horizontalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        selectedSymptomsLabel = new QLabel(symptomsPage);
        selectedSymptomsLabel->setObjectName("selectedSymptomsLabel");

        verticalLayout_6->addWidget(selectedSymptomsLabel);

        selectedSymptomList = new QListWidget(symptomsPage);
        selectedSymptomList->setObjectName("selectedSymptomList");

        verticalLayout_6->addWidget(selectedSymptomList);

        removeSymptomButton = new QPushButton(symptomsPage);
        removeSymptomButton->setObjectName("removeSymptomButton");

        verticalLayout_6->addWidget(removeSymptomButton);


        horizontalLayout_2->addLayout(verticalLayout_6);


        verticalLayout_4->addLayout(horizontalLayout_2);

        stackedWidget->addWidget(symptomsPage);
        medicalHistoryPage = new QWidget();
        medicalHistoryPage->setObjectName("medicalHistoryPage");
        verticalLayout_7 = new QVBoxLayout(medicalHistoryPage);
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_4 = new QLabel(medicalHistoryPage);
        label_4->setObjectName("label_4");
        label_4->setFont(font);

        verticalLayout_7->addWidget(label_4);

        medicalHistoryLabel = new QLabel(medicalHistoryPage);
        medicalHistoryLabel->setObjectName("medicalHistoryLabel");

        verticalLayout_7->addWidget(medicalHistoryLabel);

        medicalHistoryTextEdit = new QTextEdit(medicalHistoryPage);
        medicalHistoryTextEdit->setObjectName("medicalHistoryTextEdit");

        verticalLayout_7->addWidget(medicalHistoryTextEdit);

        familyHistoryLabel = new QLabel(medicalHistoryPage);
        familyHistoryLabel->setObjectName("familyHistoryLabel");

        verticalLayout_7->addWidget(familyHistoryLabel);

        familyHistoryTextEdit = new QTextEdit(medicalHistoryPage);
        familyHistoryTextEdit->setObjectName("familyHistoryTextEdit");

        verticalLayout_7->addWidget(familyHistoryTextEdit);

        medicationsLabel = new QLabel(medicalHistoryPage);
        medicationsLabel->setObjectName("medicationsLabel");

        verticalLayout_7->addWidget(medicationsLabel);

        medicationsTextEdit = new QTextEdit(medicalHistoryPage);
        medicationsTextEdit->setObjectName("medicationsTextEdit");

        verticalLayout_7->addWidget(medicationsTextEdit);

        allergiesCheckBox = new QCheckBox(medicalHistoryPage);
        allergiesCheckBox->setObjectName("allergiesCheckBox");

        verticalLayout_7->addWidget(allergiesCheckBox);

        allergiesTextEdit = new QTextEdit(medicalHistoryPage);
        allergiesTextEdit->setObjectName("allergiesTextEdit");

        verticalLayout_7->addWidget(allergiesTextEdit);

        stackedWidget->addWidget(medicalHistoryPage);

        verticalLayout->addWidget(stackedWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        cancelButton = new QPushButton(PatientForm);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);

        backButton = new QPushButton(PatientForm);
        backButton->setObjectName("backButton");

        horizontalLayout->addWidget(backButton);

        nextButton = new QPushButton(PatientForm);
        nextButton->setObjectName("nextButton");

        horizontalLayout->addWidget(nextButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(PatientForm);

        QMetaObject::connectSlotsByName(PatientForm);
    } // setupUi

    void retranslateUi(QWidget *PatientForm)
    {
        PatientForm->setWindowTitle(QCoreApplication::translate("PatientForm", "Patient Information", nullptr));
        label->setText(QCoreApplication::translate("PatientForm", "Personal Information", nullptr));
        nameLabel->setText(QCoreApplication::translate("PatientForm", "Full Name:", nullptr));
        dobLabel->setText(QCoreApplication::translate("PatientForm", "Date of Birth:", nullptr));
        genderLabel->setText(QCoreApplication::translate("PatientForm", "Gender:", nullptr));
        contactLabel->setText(QCoreApplication::translate("PatientForm", "Contact Number:", nullptr));
        emergencyContactLabel->setText(QCoreApplication::translate("PatientForm", "Emergency Contact:", nullptr));
        addressLabel->setText(QCoreApplication::translate("PatientForm", "Address:", nullptr));
        label_2->setText(QCoreApplication::translate("PatientForm", "Insurance Information", nullptr));
        hasInsuranceRadio->setText(QCoreApplication::translate("PatientForm", "I have insurance", nullptr));
        insuranceGroupBox->setTitle(QCoreApplication::translate("PatientForm", "Insurance Details", nullptr));
        providerLabel->setText(QCoreApplication::translate("PatientForm", "Insurance Provider:", nullptr));
        memberIdLabel->setText(QCoreApplication::translate("PatientForm", "Member ID:", nullptr));
        label_3->setText(QCoreApplication::translate("PatientForm", "Symptoms", nullptr));
        availableSymptomsLabel->setText(QCoreApplication::translate("PatientForm", "Available Symptoms:", nullptr));
        severityLabel->setText(QCoreApplication::translate("PatientForm", "Severity (1-5):", nullptr));
        addSymptomButton->setText(QCoreApplication::translate("PatientForm", "Add Symptom", nullptr));
        selectedSymptomsLabel->setText(QCoreApplication::translate("PatientForm", "Selected Symptoms:", nullptr));
        removeSymptomButton->setText(QCoreApplication::translate("PatientForm", "Remove Selected Symptom", nullptr));
        label_4->setText(QCoreApplication::translate("PatientForm", "Medical History", nullptr));
        medicalHistoryLabel->setText(QCoreApplication::translate("PatientForm", "Personal Medical History:", nullptr));
        familyHistoryLabel->setText(QCoreApplication::translate("PatientForm", "Family Medical History:", nullptr));
        medicationsLabel->setText(QCoreApplication::translate("PatientForm", "Current Medications:", nullptr));
        allergiesCheckBox->setText(QCoreApplication::translate("PatientForm", "I have medication allergies", nullptr));
        cancelButton->setText(QCoreApplication::translate("PatientForm", "Cancel", nullptr));
        backButton->setText(QCoreApplication::translate("PatientForm", "Back", nullptr));
        nextButton->setText(QCoreApplication::translate("PatientForm", "Next", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PatientForm: public Ui_PatientForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTFORM_H
