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

win32:INCLUDEPATH += X:\opencv\build

win32:LIBS += X:\opencv-build\bin\libopencv_core331.dll
win32:LIBS += X:\opencv-build\bin\libopencv_highgui331.dll
win32:LIBS += X:\opencv-build\bin\libopencv_imgcodecs331.dll
win32:LIBS += X:\opencv-build\bin\libopencv_imgproc331.dll
win32:LIBS += X:\opencv-build\bin\libopencv_features2d331.dll
win32:LIBS += X:\opencv-build\bin\libopencv_calib3d331.dll

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> parent of 97edcd1... nameconvention
# more correct variant, how set includepath and libs for mingw
# add system variable: OPENCV_SDK_DIR=D:/opencv/build
# read http://doc.qt.io/qt-5/qmake-variable-reference.html#libs

<<<<<<< HEAD
>>>>>>> b5d9aa4253e32aa01ec4d7900b861fe306ff70ad
unix:INCLUDEPATH += /usr/local/include/opencv
unix:INCLUDEPATH += /usr/local/include
unix:LIBS += -L/usr/local/lib -lopencv_dnn -lopencv_ml -lopencv_objdetect -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_imgproc -lopencv_flann -lopencv_core
unix:LIBS += -lXtst -lX11
=======
unix:LIBS += -L/usr/local/lib -lmath

#INCLUDEPATH += $$(OPENCV_SDK_DIR)/include

#LIBS += -L$$(OPENCV_SDK_DIR)/x86/mingw/lib \
#        -lopencv_core331        \
#        -lopencv_highgui331     \
#        -lopencv_imgcodecs331   \
#        -lopencv_imgproc331     \
#        -lopencv_features2d331  \
#        -lopencv_calib3d331

#ifdef __linux
    #include <X11/Xlib.h>
    #include <X11/keysym.h>

    void mouseClick(int x, int y){
        QCursor mouse;
        mouse.setPos(x + screenX,y + screenY);

        XEvent event;
        memset (&event, 0, sizeof (event));
        event.xbutton.button = button;
        event.xbutton.same_screen = True;
        event.xbutton.subwindow = DefaultRootWindow (display);
        while (event.xbutton.subwindow)
        {
          event.xbutton.window = event.xbutton.subwindow;
          XQueryPointer (display, event.xbutton.window,
                         &event.xbutton.root, &event.xbutton.subwindow,
                         &event.xbutton.x_root, &event.xbutton.y_root,
                         &event.xbutton.x, &event.xbutton.y,
                         &event.xbutton.state);
        }
        // Press
        event.type = ButtonPress;
        if (XSendEvent (display, PointerWindow, True, ButtonPressMask, &event) == 0)
        fprintf (stderr, "Error to send the event!\n");
        XFlush (display);
        usleep (1);
        // Release
        event.type = ButtonRelease;
        if (XSendEvent (display, PointerWindow, True, ButtonReleaseMask, &event) == 0)
        fprintf (stderr, "Error to send the event!\n");
        XFlush (display);
        usleep (1);
    }
#else
    #include <windows.h>

    void mouseClick(int x, int y){
        QCursor mouse;
        mouse.setPos(x + screenX,y + screenY);
        mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 1, 1, 0, 0);
    }
#endif
>>>>>>> parent of 97edcd1... nameconvention
