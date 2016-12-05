TEMPLATE = lib
CONFIG -= qtc_runnable

QT += quick quickcontrols2 sql
android:QT+= androidextras

include(../main/common.pri)
LIBS += -L$$DESTDIR -lassets

DEFINES += UNTITLED_LIB

#no_include_pwd
SOURCES += \
    levelpicker.cpp \
    level.cpp \
    score.cpp \
    scorethingee.cpp \
    languagethingee.cpp \
    book.cpp \
    untitled.cpp \
    form1viewmodel.cpp

HEADERS += \
    levelpicker.h \
    level.h \
    score.h \
    models.h \
    scorethingee.h \
    languagethingee.h \
    book.h \
    untitled.h \
    form1viewmodel.h


# delrcc =$$system_path($$absolute_path($$RCC_DIR)/qrc_qml.*)
# out = $$system(del /q $$delrcc)
