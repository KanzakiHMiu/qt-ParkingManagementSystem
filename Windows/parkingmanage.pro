QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    allowedinout.cpp \
    databasemanager.cpp \
    login_admin.cpp \
    main.cpp \
    mainwindow.cpp \
    netmanager.cpp \
    opencvrecog.cpp \
    spotsrecog.cpp \
    sysabout.cpp

HEADERS += \
    allowedinout.h \
    databasemanager.h \
    login_admin.h \
    mainwindow.h \
    netmanager.h \
    opencvrecog.h \
    spotsrecog.h \
    sysabout.h

FORMS += \
    login_admin.ui \
    mainwindow.ui \
    sysabout.ui

INCLUDEPATH += G:/qfile/1466900310/FileRecv/opencv/build/include
LIBS += G:/qfile/1466900310/FileRecv/opencv/opencv_build/bin/libopencv_core490.dll
LIBS += G:/qfile/1466900310/FileRecv/opencv/opencv_build/bin/libopencv_highgui490.dll
LIBS += G:/qfile/1466900310/FileRecv/opencv/opencv_build/bin/libopencv_imgcodecs490.dll
LIBS += G:/qfile/1466900310/FileRecv/opencv/opencv_build/bin/libopencv_imgproc490.dll
LIBS += G:/qfile/1466900310/FileRecv/opencv/opencv_build/bin/libopencv_features2d490.dll
LIBS += G:/qfile/1466900310/FileRecv/opencv/opencv_build/bin/libopencv_calib3d490.dll

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
