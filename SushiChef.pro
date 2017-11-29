#-------------------------------------------------
#
# Project created by QtCreator 2017-03-05T12:30:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opencvtest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp

HEADERS  +=

win32:INCLUDEPATH += X:\opencv\build\include

win32:LIBS += X:\opencv-build\bin\libopencv_core331.dll
win32:LIBS += X:\opencv-build\bin\libopencv_highgui331.dll
win32:LIBS += X:\opencv-build\bin\libopencv_imgcodecs331.dll
win32:LIBS += X:\opencv-build\bin\libopencv_imgproc331.dll
win32:LIBS += X:\opencv-build\bin\libopencv_features2d331.dll
win32:LIBS += X:\opencv-build\bin\libopencv_calib3d331.dll

unix:INCLUDEPATH += /usr/local/include/opencv
unix:INCLUDEPATH += /usr/local/include
unix:LIBS += -L/usr/local/lib -lopencv_dnn -lopencv_ml -lopencv_objdetect -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core
unix:LIBS += -lXtst -lX11
