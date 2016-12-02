TEMPLATE = subdirs

SUBDIRS = \
  ../assets \
  ../untitled

win32: {
  SUBDIRS += ../tests
}

untitled.depends = assets
tests.depends = untitled
