#ifndef PLATFORMTHINGEE_H
#define PLATFORMTHINGEE_H
namespace untitled {
class PlatformThingee {
public:
  virtual void ready() = 0;
  virtual void show() = 0;
  virtual void hide() = 0;

  virtual ~PlatformThingee() {}
};
}
#endif // PLATFORMTHINGEE_H
