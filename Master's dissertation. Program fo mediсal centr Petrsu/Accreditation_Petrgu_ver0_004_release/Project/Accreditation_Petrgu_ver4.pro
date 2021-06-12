#-------------------------------------------------
#
# Project created by QtCreator 2019-05-17T19:10:16
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Accreditation_Petrgu_ver4_0
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        checklabels.cpp \
        checklabelscs.cpp \
        cickletimerform.cpp \
        clientform.cpp \
        clientserverform.cpp \
        clientwindow.cpp \
        cmdform.cpp \
        detectfaces.cpp \
        hid.c \
        ipcamera.cpp \
        logfile.cpp \
        main.cpp \
        mainwindow.cpp \
        moduleusbform.cpp \
        optionsform.cpp \
        ptzcameraform.cpp \
        saveform.cpp \
        serverform.cpp \
        threadanalyze.cpp \
        threadangle.cpp \
        threadcapture.cpp \
        videoform.cpp \
        videoregistratorform.cpp

LIBS += -lSetupAPI

HEADERS += \
        checklabels.h \
        checklabelscs.h \
        cickletimerform.h \
        clientform.h \
        clientserverform.h \
        clientwindow.h \
        cmdform.h \
        detectfaces.h \
        hidapi.h \
        logfile.h \
        ipcamera.h \
        mainwindow.h \
        moduleusbform.h \
        optionsform.h \
        ptzcameraform.h \
        saveform.h \
        serverform.h \
        threadanalyze.h \
        threadangle.h \
        threadcapture.h \
        videoform.h \
        videoregistratorform.h \
        #hikvision lib
        ./HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/incEn/HCNetSDK.h \
        ./HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/incEn/plaympeg4.h \
        ./HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/incEn/DataType.h \
        ./HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/incEn/DecodeCardSdk.h \

FORMS += \
        cickletimerform.ui \
        clientform.ui \
        clientserverform.ui \
        cmdform.ui \
        mainwindow.ui \
        moduleusbform.ui \
        optionsform.ui \
        ptzcameraform.ui \
        saveform.ui \
        serverform.ui \
        videoform.ui \
        videoregistratorform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

#Прописываем путь к заголовочным файлам
INCLUDEPATH += \
    . \
    #hikvision lib
    ./HCNetSDKV5.3.1.30_build20170904_win32/ \
    ./HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/incEn/ \
    ./HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/lib/win32/ \
    ./HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/lib/win32/ClientDemoDll/ \
    #opencv4 lib
    ./opencv/build/include \

#Прописываем путь к библиотекам
LIBS += \
    #hikvision lib
    $$PWD/HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/lib/win32/HCNetSDK.lib \
    $$PWD/HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/lib/win32/HCCore.lib \
    $$PWD/HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/lib/win32/PlayCtrl.lib \
    $$PWD/HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/lib/win32/HCNetSDK.lib \
    $$PWD/HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/lib/win32/HCNetSDKCom/HCAlarm.lib \
    $$PWD/HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/lib/win32/HCNetSDKCom/HCGeneralCfgMgr.lib \
    $$PWD/HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/lib/win32/HCNetSDKCom/HCPreview.lib \
    "-L$$PWD/HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/lib/win32/" \
    "-L$$PWD/HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/lib/win32/ClientDemoDll/" \
    "-L$$PWD/HCNetSDKV5.3.1.30_build20170904_win32/HCNetSDKV5.3.1.30_build20170904_win32_EN/lib/win32/HCNetSDKCom/" \
    #opencv4 lib
    "-L$$PWD/opencv/my-build-mingw/bin/" \
    $$PWD/opencv/my-build-mingw/bin/libopencv_core401.dll \
    $$PWD/opencv/my-build-mingw/bin/libopencv_highgui401.dll \
    $$PWD/opencv/my-build-mingw/bin/libopencv_imgcodecs401.dll \
    $$PWD/opencv/my-build-mingw/bin/libopencv_imgproc401.dll \
    $$PWD/opencv/my-build-mingw/bin/libopencv_features2d401.dll \
    $$PWD/opencv/my-build-mingw/bin/libopencv_calib3d401.dll \
    $$PWD/opencv/my-build-mingw/bin/libopencv_video401.dll \
    $$PWD/opencv/my-build-mingw/bin/libopencv_videoio401d.dll \
    #Дополнительные библиотеки для распознавания лиц
    $$PWD/opencv/my-build-mingw/bin/libopencv_objdetect401.dll \
    $$PWD/opencv/my-build-mingw/bin/libopencv_imgproc401.dll
