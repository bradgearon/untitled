#include "winplatformthingee.h"

using namespace untitled;

WinPlatformThingee::WinPlatformThingee() {
  app = static_cast<QGuiApplication *>(QGuiApplication::instance());
}

void WinPlatformThingee::ready() {}

void WinPlatformThingee::show() {
  qDebug() << "showing";
  app->focusWindow()->show();
}

void WinPlatformThingee::hide() {
  qDebug() << "hiding";
  app->focusWindow()->hide();
}

WinPlatformThingee::~WinPlatformThingee() {}
