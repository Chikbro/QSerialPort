QT       += core gui
QT      += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
TARGET = my_shag
TEMPLATE = app


SOURCES += main.cpp\
    Buffer.cpp \
    Supervisordevice.cpp \
        mainwindow.cpp \
    port.cpp

HEADERS  += mainwindow.h \
    BattarySupervisorCMDFactory.h \
    BattarySupervisorCMDProvider.h \
    Buffer.h \
    Command.h \
    CommandFactory.h \
    CommandID.h \
    CommandProvider.h \
    DeviceCategory.h \
    DeviceID.h \
    Manufacturer.h \
    Params.h \
    PassportDevice.h \
    ServiceData.h \
    Supervisordevice.h \
    port.h

FORMS    += mainwindow.ui
