TEMPLATE = subdirs

SUBDIRS = \
    ../zlib-1.2.8 \
    ../quazip \
    ../unity-ads-qt

quazip.depends = zlib-1.2.8

unity-ads-qt.depends = quazip
