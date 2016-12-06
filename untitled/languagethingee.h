#pragma once

#include "models.h"

namespace untitled {

class LanguageThingee {
public:
  LanguageThingee();
  void setConfig(QString language);
  Element getElementByName(QString name);

private:
};
}
