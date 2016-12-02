QT += quick quickcontrols2 sql

include(../main/common.pri)

#todo: make sure this is ok
QT -= network

RESOURCES += qml.qrc

LIBS += -L$$DESTDIR -lassets

SOURCES += main.cpp \
    levelpicker.cpp \
    level.cpp \
    score.cpp \
    scorethingee.cpp \
    languagethingee.cpp \
    book.cpp

HEADERS += \
    levelpicker.h \
    level.h \
    score.h \
    models.h \
    scorethingee.h \
    languagethingee.h \
    book.h

