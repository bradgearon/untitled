#ifndef UNTITLED_H
#define UNTITLED_H

#include <QtCore/qcompilerdetection.h>

#if defined UNTITLED_LIB
#define UNTITLED_COMMON_DLLSPEC Q_DECL_EXPORT
#else
#define UNTITLED_COMMON_DLLSPEC Q_DECL_IMPORT
#endif

extern "C" UNTITLED_COMMON_DLLSPEC int untitled_start(int argc = 0,
                                                      char *argv[] = nullptr);

#endif // UNTITLED_H
