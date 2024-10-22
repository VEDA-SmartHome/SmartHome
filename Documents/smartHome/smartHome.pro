QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatroomdialog.cpp \
    chatwidgetformanager.cpp \
    chatwidgetforresident.cpp \
    household.cpp \
    householdcontrolwidget.cpp \
    householdmanager.cpp \
    login.cpp \
    loginwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    manager.cpp \
    managermanager.cpp \
    person.cpp \
    resident.cpp \
    residentcontrolwidget.cpp \
    residenthomewidget.cpp \
    residentmanager.cpp \
    sensorcontrolwidget.cpp

HEADERS += \
    chatroomdialog.h \
    chatwidgetformanager.h \
    chatwidgetforresident.h \
    household.h \
    householdcontrolwidget.h \
    householdmanager.h \
    login.h \
    loginwidget.h \
    mainwindow.h \
    manager.h \
    managermanager.h \
    person.h \
    resident.h \
    residentcontrolwidget.h \
    residenthomewidget.h \
    residentmanager.h \
    sensorcontrolwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    chatroomdialog.ui \
    chatwidgetformanager.ui \
    chatwidgetforresident.ui \
    householdcontrolwidget.ui \
    loginwidget.ui \
    residentcontrolwidget.ui \
    residenthomewidget.ui \
    sensorcontrolwidget.ui

RESOURCES += \
    resources.qrc
