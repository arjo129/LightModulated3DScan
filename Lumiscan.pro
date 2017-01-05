#-------------------------------------------------
#
# Project created by QtCreator 2017-01-02T15:04:38
#
#-------------------------------------------------

QT       += core gui serialport multimedia charts datavisualization multimediawidgets widgets
LIBS += -L/usr/local/lib -lopencv_shape -lopencv_stitching -lopencv_objdetect -lopencv_superres -lopencv_videostab -lopencv_calib3d -lopencv_features2d -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_video -lopencv_photo -lopencv_ml -lopencv_imgproc -lopencv_flann -lopencv_core
QMAKE_CXXFLAGS += -I/usr/local/include/opencv -I/usr/local/include

TARGET = Lumiscan
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    captureimage.cpp

HEADERS  += mainwindow.h \
    captureimage.h

FORMS    += mainwindow.ui
