QT      += core gui
QT      += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = my_app
TEMPLATE = app

SOURCES += main.cpp\
    Buffer.cpp \
    mainwindow.cpp \
    port.cpp

HEADERS  += mainwindow.h \
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
    Status.h \
    crc.h \
    port.h \
    protocoldefc.h

FORMS    += mainwindow.ui
