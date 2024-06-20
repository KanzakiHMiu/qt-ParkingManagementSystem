QT       += core gui
QT       +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bill.cpp \
    billwidget.cpp \
    changeinfo.cpp \
    first.cpp \
    main.cpp \
    myinfo.cpp \
    pay.cpp \
    walet.cpp \
    widget.cpp

HEADERS += \
    bill.h \
    billwidget.h \
    changeinfo.h \
    first.h \
    myinfo.h \
    pay.h \
    walet.h \
    widget.h

FORMS += \
    bill.ui \
    billwidget.ui \
    changeinfo.ui \
    first.ui \
    myinfo.ui \
    pay.ui \
    walet.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
