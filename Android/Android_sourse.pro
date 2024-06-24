QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bill.cpp \
    changeinfo.cpp \
    firstpage.cpp \
    main.cpp \
    netmanager.cpp \
    pay.cpp \
    wallet.cpp \
    widget.cpp

HEADERS += \
    bill.h \
    changeinfo.h \
    firstpage.h \
    netmanager.h \
    pay.h \
    wallet.h \
    widget.h

FORMS += \
    bill.ui \
    changeinfo.ui \
    firstpage.ui \
    pay.ui \
    wallet.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc

contains(ANDROID_TARGET_ARCH,x86_64) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

DISTFILES += \
    android/AndroidManifest.xml
