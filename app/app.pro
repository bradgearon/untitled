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

win32:RESOURCES += ../untitled/qml.qrc

DISTFILES += \
    empty.qml \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/res/values/styles.xml \
    android/src/com/wds/untitled/UntitledNative.java \
    android/src/com/wds/untitled/MyActivity.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

