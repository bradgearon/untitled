#ifndef WINPLATFORMTHINGEE_H
#define WINPLATFORMTHINGEE_H

#include "platformthingee.h"
#include <QDebug>
#include <QGuiApplication>
#include <QWindow>

namespace untitled {
class WinPlatformThingee : public PlatformThingee {
public:
  WinPlatformThingee();
  void ready();
  void show();
  void hide();
  ~WinPlatformThingee();

private:
  QGuiApplication *app;
};
}
#endif // WINPLATFORMTHINGEE_H
