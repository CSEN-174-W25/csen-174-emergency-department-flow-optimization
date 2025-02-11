/****************************************************************************
** Meta object code from reading C++ file 'test_cases.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../test_cases.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'test_cases.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASStest_casesENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASStest_casesENDCLASS = QtMocHelpers::stringData(
    "test_cases",
    "test_add_symptom",
    "",
    "test_remove_symptom",
    "test_has_symptom",
    "test_get_detailed_department_recommendation",
    "test_calculate_overall_urgency",
    "test_get_symptoms",
    "test_get_symptom_count",
    "test_has_additional_symptoms",
    "test_set_additional_symptoms"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASStest_casesENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   68,    2, 0x08,    1 /* Private */,
       3,    0,   69,    2, 0x08,    2 /* Private */,
       4,    0,   70,    2, 0x08,    3 /* Private */,
       5,    0,   71,    2, 0x08,    4 /* Private */,
       6,    0,   72,    2, 0x08,    5 /* Private */,
       7,    0,   73,    2, 0x08,    6 /* Private */,
       8,    0,   74,    2, 0x08,    7 /* Private */,
       9,    0,   75,    2, 0x08,    8 /* Private */,
      10,    0,   76,    2, 0x08,    9 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject test_cases::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASStest_casesENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASStest_casesENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASStest_casesENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<test_cases, std::true_type>,
        // method 'test_add_symptom'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'test_remove_symptom'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'test_has_symptom'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'test_get_detailed_department_recommendation'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'test_calculate_overall_urgency'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'test_get_symptoms'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'test_get_symptom_count'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'test_has_additional_symptoms'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'test_set_additional_symptoms'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void test_cases::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<test_cases *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->test_add_symptom(); break;
        case 1: _t->test_remove_symptom(); break;
        case 2: _t->test_has_symptom(); break;
        case 3: _t->test_get_detailed_department_recommendation(); break;
        case 4: _t->test_calculate_overall_urgency(); break;
        case 5: _t->test_get_symptoms(); break;
        case 6: _t->test_get_symptom_count(); break;
        case 7: _t->test_has_additional_symptoms(); break;
        case 8: _t->test_set_additional_symptoms(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *test_cases::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *test_cases::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASStest_casesENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int test_cases::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
