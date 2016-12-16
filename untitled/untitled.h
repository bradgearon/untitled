#ifndef UNTITLED_H
#define UNTITLED_H

#include "maincontroller.h"

#include <QtCore/qcompilerdetection.h>

#if defined UNTITLED_LIB
#define UNTITLED_COMMON_DLLSPEC Q_DECL_EXPORT
#else
#define UNTITLED_COMMON_DLLSPEC Q_DECL_IMPORT
#endif
extern "C" {
UNTITLED_COMMON_DLLSPEC int untitled_init(int argc = 0, char *argv[] = nullptr);
UNTITLED_COMMON_DLLSPEC void untitled_show();
UNTITLED_COMMON_DLLSPEC void untitled_hide();
}

#endif // UNTITLED_H
