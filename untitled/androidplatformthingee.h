#ifndef ANDROIDPLATFORMTHINGEE_H
#define ANDROIDPLATFORMTHINGEE_H

#include "platformthingee.h"
#include <QGuiApplication>
#include <QtAndroidExtras>

namespace untitled {
class AndroidPlatformThingee : public PlatformThingee {
public:
  AndroidPlatformThingee();
  void ready();
  void show();
  void hide();
  ~AndroidPlatformThingee();

private:
  const char *helper = "com/wds/untitled/UntitledNative";
  QAndroidJniObject activity;
};
}
#endif // ANDROIDPLATFORMTHINGEE_H
