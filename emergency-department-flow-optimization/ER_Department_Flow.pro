QT       += core gui \
            core testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    department.cpp \
    main.cpp \
    mainwindow.cpp \
    nurse.cpp \
    nurseinterface.cpp \
    nurselogin.cpp \
    patient.cpp \
    patientform.cpp \
    symptom_definition.cpp \
    symptoms.cpp \
    tests.cpp

HEADERS += \
    department.h \
    main.h \
    mainwindow.h \
    nurse.h \
    nurseinterface.h \
    nurselogin.h \
    patient.h \
    patientform.h \
    symptom_definition.h \
    symptoms.h \
    tests.h

FORMS += \
    mainwindow.ui \
    nurseinterface.ui \
    nurselogin.ui \
    patientform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ER_Department_Flow.pro.user
