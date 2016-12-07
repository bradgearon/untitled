#pragma once

#include "loadermoboberjigger.h"

namespace untitled {

class LanguageThingee {
public:
  LanguageThingee(LoaderMoboberJigger loader);
  void setConfig(QString language);
  Element getElementByName(QString name);

private:
  LoaderMoboberJigger loader;
  Config *config;
  std::map<QString, Book *> bookMap;
};
}
