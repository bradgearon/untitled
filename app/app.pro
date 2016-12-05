TEMPLATE = app
QT += qml quick quickcontrols2 sql
android:QT+= androidextras

DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += qml_debug

include(../main/common.pri)

LIBS += -L$$DESTDIR -luntitled
LIBS += -L$$DESTDIR -lassets

INCLUDEPATH += ../untitled
DEPENDPATH += ../untitled

SOURCES += \
    main.cpp

DISTFILES += \
    empty.qml

RESOURCES += ../untitled/qml.qrc

