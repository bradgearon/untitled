TEMPLATE = app
TARGET = untitled
QT += quick qml quickcontrols2 sql network
CONFIG += c++14 release
CONFIG -= debug debug_and_release
DEFINES += QT_DEPRECATED_WARNINGS UNTITLED_LIB UNTITLED_STANDALONE
INCLUDEPATH += $$PWD/untitled
SOURCES += $$PWD/app/main.cpp \
    $$PWD/untitled/levelpicker.cpp \
    $$PWD/untitled/level.cpp \
    $$PWD/untitled/score.cpp \
    $$PWD/untitled/scorethingee.cpp \
    $$PWD/untitled/languagethingee.cpp \
    $$PWD/untitled/book.cpp \
    $$PWD/untitled/untitled.cpp \
    $$PWD/untitled/form1viewmodel.cpp \
    $$PWD/untitled/element.cpp \
    $$PWD/untitled/loadermoboberjigger.cpp \
    $$PWD/untitled/config.cpp \
    $$PWD/untitled/maincontroller.cpp
HEADERS += $$files($$PWD/untitled/*.h)
HEADERS -= $$PWD/untitled/androidplatformthingee.h
RESOURCES += $$PWD/assets/assets.qrc $$PWD/untitled/qml.qrc
QMAKE_RESOURCE_FLAGS += -compress 5 -threshold 0
win32 {
    DEFINES += WIN32
    SOURCES += $$PWD/untitled/winplatformthingee.cpp
}
android {
    QT += androidextras
    DEFINES += ANDROID
    SOURCES += $$PWD/untitled/androidplatformthingee.cpp
    HEADERS += $$PWD/untitled/androidplatformthingee.h
    ANDROID_PACKAGE_SOURCE_DIR = $$OUT_PWD/package
    ANDROID_MIN_SDK_VERSION = 23
    ANDROID_TARGET_SDK_VERSION = 29
}
include($$PWD/libs/qt-google-analytics/qt-google-analytics.pri)
