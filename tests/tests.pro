QT += core sql

TARGET = tests

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

include(../main/common.pri)

TEST = $$files($$OBJECTS_DIR/*.o*)
for(object, TEST) {
  uhh = $$find(object, main)
  count(uhh, 0) {
    OBJECTS += $$object
    message($$object)
  }
}



INCLUDEPATH += ../untitled

SOURCES += testlevelpicker.cpp

OTHER_FILES += \
  level.json

HEADERS += \
    tests.h

DESTDIR = build/$$PLATFORM
