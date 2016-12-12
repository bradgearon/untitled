#include "androidplatformthingee.h"

using namespace untitled;

AndroidPlatformThingee::AndroidPlatformThingee() {
  activity = QtAndroid::androidActivity();
}

void AndroidPlatformThingee::ready() {}

void AndroidPlatformThingee::show() {
  qDebug() << "showing qtactivity";
  QAndroidJniObject::callStaticMethod<void>(
      helper, "bringToFront", "(Landroid/app/Activity;)V",
      QtAndroid::androidActivity().object());
}

void AndroidPlatformThingee::hide() {
  qDebug() << "hiding qtactivity";
  QAndroidJniObject::callStaticMethod<void>(
      helper, "sendToBack", "(Landroid/app/Activity;)V",
      QtAndroid::androidActivity().object());
  qDebug() << "qtactivity hidden";
}

AndroidPlatformThingee::~AndroidPlatformThingee() {}
