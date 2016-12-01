TEMPLATE = subdirs
# CONFIG += qtc_runnable

SUBDIRS = \
  ../untitled

win32: {
SUBDIRS += ../tests
}

tests.depends = untitled
