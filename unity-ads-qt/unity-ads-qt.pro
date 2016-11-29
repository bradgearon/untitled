TEMPLATE = app
QT += qml quick webview

SOURCES += main.cpp \
    pageaction.cpp
RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model

INCLUDEPATH += $$PWD\..\zlib-1.2.8
LIBS += -L..\zlib-1.2.8 -lz

INCLUDEPATH += $${PWD}\..\quazip\quazip
LIBS += -L..\quazip -lquazip

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    main.h \
    pageaction.h

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

DISTFILES += \
    $$ANDROID_PACKAGE_SOURCE_DIR/AndroidManifest.xml \
    $$ANDROID_PACKAGE_SOURCE_DIR/gradle/wrapper/gradle-wrapper.jar \
    $$ANDROID_PACKAGE_SOURCE_DIR/gradlew \
    $$ANDROID_PACKAGE_SOURCE_DIR/res/values/libs.xml \
    $$ANDROID_PACKAGE_SOURCE_DIR/build.gradle \
    $$ANDROID_PACKAGE_SOURCE_DIR/gradle/wrapper/gradle-wrapper.properties \
    $$ANDROID_PACKAGE_SOURCE_DIR/gradlew.bat

ANDROID_JAVA_SOURCES.path = $$ANDROID_PACKAGE_SOURCE_DIR/src
ANDROID_JAVA_SOURCES.files = $$files($$PWD/**/*.java)

INSTALLS += ANDROID_JAVA_SOURCES
