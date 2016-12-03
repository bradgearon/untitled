CONFIG += c++14
CONFIG-=qml_debug

linux: {
  PLATFORM = linux
}

win32: {
  DEFINES += WIN32
  PLATFORM = win32
  EXT = exe
}

android: {
  PLATFORM = android
}

MOC_DIR = ../build/$$PLATFORM/obj
OBJECTS_DIR = ../build/$$PLATFORM/obj
DESTDIR = ../build/$$PLATFORM
RCC_DIR = ../build/$$PLATFORM/obj
