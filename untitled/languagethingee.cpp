#include "languagethingee.h"
using namespace untitled;

LanguageThingee::LanguageThingee(LoaderMoboberJigger loader) {
  this->loader = loader;
  bookMap = loader.loadBooks();
}

void LanguageThingee::setConfig(QString language) {
  config = loader.loadConfig(language);
}

Element LanguageThingee::getElementByName(QString name) {}
