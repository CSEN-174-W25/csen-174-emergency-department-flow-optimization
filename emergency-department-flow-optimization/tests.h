#ifndef TESTS_H
#define TESTS_H

#include <QObject>
#include <QTest>

class tests: public QObject
{
    Q_OBJECT
    public:
        tests();

    private slots:
        void addPatient();
};

#endif // TESTS_H
