#pragma once

#include "loadermoboberjigger.h"

namespace untitled {

class LanguageThingee {
public:
  LanguageThingee(LoaderMoboberJigger loader);
  Config *setConfig(QString language);
  Element *getElementByName(QString name);

private:
  LoaderMoboberJigger loader;
  Config *config;
  std::map<QString, Book *> bookMap;
  QString interpolate(QString string, QString version, QStringList parts);
  Book *book;
  Element *element;
};
}
