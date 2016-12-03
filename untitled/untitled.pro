QT += quick quickcontrols2 sql

include(../main/common.pri)

RESOURCES += qml.qrc

LIBS += -L$$DESTDIR -lassets

#no_include_pwd
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


