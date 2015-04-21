#-------------------------------------------------
#
# Project created by QtCreator 2014-09-05T20:58:41
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
CONFIG   += console
RC_FILE  += myico.rc
QT       +=network
CONFIG   +=C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PTZ_TargetTracking
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    stdafx.cpp \
    targetTracking.cpp \
    information_feedback_class.cpp \
    my_serialport_class.cpp \
    PTZ_command_class.cpp \
    FaceDection.cpp \
    ImageCotroller.cpp \
    FaceRecongnition.cpp \
    BrowseDir.cpp

HEADERS  += mainwindow.h \
    stdafx.h \
    targetver.h \
    targetTracking.h \
    information_feedback_class.h \
    my_serialport_class.h \
    PTZ_command_class.h \
    FaceDetection.h \
    ImageController.h \
    FaceRecognition.h \
    BrowseDir.h \
    StatDir.h \
    WatershedSegment.h

FORMS    += mainwindow.ui
INCLUDEPATH += D:/opencv/build/include
INCLUDEPATH += D:/opencv/build/include/opencv
INCLUDEPATH += D:/opencv/build/include/opencv2

win32:CONFIG(debug, debug|release): {
LIBS += -LD:/opencV/build/x86/vc11/lib \
-lopencv_core249d \
-lopencv_imgproc249d \
-lopencv_highgui249d \
-lopencv_ml249d \
-lopencv_video249d \
-lopencv_features2d249d \
-lopencv_calib3d249d \
-lopencv_objdetect249d \
-lopencv_contrib249d \
-lopencv_legacy249d \
-lopencv_flann249d\
} else:win32:CONFIG(release, debug|release): {
LIBS += -LD:/opencv/build/x86/vc11/lib \
-lopencv_core249 \
-lopencv_imgproc249 \
-lopencv_highgui249 \
-lopencv_ml249 \
-lopencv_video249 \
-lopencv_features2d249 \
-lopencv_calib3d249 \
-lopencv_objdetect249 \
-lopencv_contrib249 \
-lopencv_legacy249 \
-lopencv_flann249
}

RESOURCES += \
    resource.qrc

