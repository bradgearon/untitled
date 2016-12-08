#include "languagethingee.h"
using namespace untitled;

LanguageThingee::LanguageThingee(LoaderMoboberJigger loader) {
  this->loader = loader;
  bookMap = loader.loadBooks();
}

Config *LanguageThingee::setConfig(QString language) {
  config = loader.loadConfig(language);
  return config;
}

Element *LanguageThingee::getElementByName(QString name) {
  auto versionObj = config->getVersion();
  auto location = name.split('-');
  book = bookMap[location[0]];

  int index = static_cast<int>(book->getIndex());
  QString version = versionObj[index];

  element = loader.loadElement(name, version);
  element->setLearnMorePath(interpolate(config->getUrl(), version, location));
  return std::move(element);
}

QString LanguageThingee::interpolate(QString url, QString version,
                                     QStringList location) {
  QStringList newUrl;
  QRegExp match("(\\w+)(?:[?*])?(.*)", Qt::CaseInsensitive);

  auto parts = url.split("//");
  newUrl << parts[0] << "//";
  size_t index = 0;
  for (auto part : parts[1].split(":")) {
    if (index++ == 0) {
      newUrl << part;
      continue;
    }

    if (match.indexIn(part) != -1) {
      auto key = match.cap(1);
      auto keyCStr = key.toStdString().c_str();

      if (key == "version") {
        newUrl << version;
      } else if (key == "chapter") {
        newUrl << location[1];
      } else if (key == "verse") {
        newUrl << location[2];
      } else if (element->property(keyCStr).isValid()) {
        newUrl << element->property(keyCStr).toString();
      } else if (config->property(keyCStr).isValid()) {
        newUrl << config->property(keyCStr).toString();
      } else if (book->property(keyCStr).isValid()) {
        newUrl << book->property(keyCStr).toString();
      }

      newUrl << match.cap(2);
    }
  }

  QString result = newUrl.join("");
  qDebug() << " read more url: " << result;
  return result;
}
