TEMPLATE = subdirs

SUBDIRS = \
  ../assets \
  ../untitled \
    ../app

win32: {
  SUBDIRS += ../tests
}

untitled.depends = assets
tests.depends = untitled
app.depends = untitled

