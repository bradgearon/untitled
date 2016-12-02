QT += quick quickcontrols2 sql
# qtc_runnable
CONFIG += c++14

QT -= widgets

win32: {
  DEFINES += WIN32
}

#build_pass:CONFIG(debug, debug) {
#  copydata.commands = $(COPY_DIR) $$system_path($$PWD/app_webview) \
#      $$system_path($$OUT_PWD/app_webview)
#  first.depends = $(first) copydata
#  export(first.depends)
#  export(copydata.commands)

#  QMAKE_EXTRA_TARGETS += first copydata
#}

RESOURCES += qml.qrc

SOURCES += main.cpp \
    bookmodel.cpp \
    levelpicker.cpp \
    level.cpp \
    score.cpp \
    scorethingee.cpp \
    languagethingee.cpp

HEADERS += \
    bookmodel.h \
    levelpicker.h \
    level.h \
    score.h \
    models.h \
    scorethingee.h \
    languagethingee.h
