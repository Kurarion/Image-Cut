# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = Qt_Vision_2
DESTDIR = ../x64/Release
QT += core gui widgets
CONFIG += release
DEFINES += WIN64 QT_DLL QT_WIDGETS_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/$(ConfigurationName)
LIBS += -lkernel32 \
    -luser32 \
    -lgdi32 \
    -lwinspool \
    -lcomdlg32 \
    -ladvapi32 \
    -lshell32 \
    -lole32 \
    -loleaut32 \
    -luuid \
    -lodbc32 \
    -lodbccp32 \
    -lopencv_calib3d2413 \
    -lopencv_contrib2413 \
    -lopencv_core2413 \
    -lopencv_features2d2413 \
    -lopencv_flann2413 \
    -lopencv_gpu2413 \
    -lopencv_highgui2413 \
    -lopencv_imgproc2413 \
    -lopencv_objdetect2413 \
    -lopencv_superres2413 \
    -lopencv_stitching2413 \
    -lopencv_photo2413 \
    -lopencv_ocl2413 \
    -lopencv_nonfree2413 \
    -lopencv_ml2413 \
    -lopencv_legacy2413 \
    -lopencv_ts2413 \
    -lopencv_video2413 \
    -lopencv_videostab2413 \
    -l$(NOINHERIT)
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(Qt_Vision_2.pri)
