
QT += core widgets
QT -= gui

CONFIG += c++11

TARGET = blinkers
CONFIG += console
CONFIG -= app_bundle

# Build
OBJECTS_DIR = $$PWD/build/obj # Intermediate object files directory
MOC_DIR = $$PWD/build/obj     # Intermediate moc files directory
UI_DIR  = $$PWD/build/obj     # UI files
RCC_DIR = $$PWD/build/obj     # Resources
DESTDIR = $$PWD/build         # Target file directory


TEMPLATE = app

SOURCES += src/main.cpp \
    src/worker.cpp \
    src/myframe.cpp \
    src/clogbook.cpp \
    src/gct.cpp \
    src/mainwindow.cpp \
    src/myqtextedit.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    src/worker.h \
    src/utils.h \
    src/myframe.h \
    src/clogbook.h \
    src/gct.h \
    src/mainwindow.h \
    src/myqtextedit.h \
    src/ui_myframe.h \
    src/ui_mainwindow.h
