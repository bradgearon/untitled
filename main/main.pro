TEMPLATE = subdirs
CONFIG += c++14

SUBDIRS = \
  ../untitled

win32: {
  SUBDIRS += ../tests
}

tests.depends = untitled
