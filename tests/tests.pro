QT += core sql
QT -= gui

CONFIG += c++11

TARGET = tests

CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

untitledObj = ../untitled/debug

OBJECTS += $${untitledObj}/levelpicker.o \
  $${untitledObj}/level.o \
  $${untitledObj}/score.o \
  $${untitledObj}/moc_score.o \
  $${untitledObj}/moc_level.o

INCLUDEPATH += ../untitled

SOURCES += main.cpp

OTHER_FILES += \
  level.json

HEADERS += \
    tests.h

