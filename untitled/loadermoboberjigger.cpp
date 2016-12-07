#include "loadermoboberjigger.h"
using namespace untitled;

LoaderMoboberJigger::LoaderMoboberJigger() {}

std::vector<std::unique_ptr<Level>> LoaderMoboberJigger::loadLevels() {
  auto levelsJson = loadJson(":/data/level.json").array();
  auto levels = getList<Level>(levelsJson);
  for (size_t i = 0; i < levels.size(); i++) {
    auto elements =
        levelsJson[static_cast<int>(i)].toObject()["elements"].toArray();
    auto level = levels[i].get();
    for (auto element : elements) {
      auto score = std::make_unique<Score>(level);

      // todo: connect Score::onValueUpdated to updateWhateverItis
      score->setName(element.toString());
      score->setRank(level->getRank());
      score->setWeight(level->getRank());
      // just use rank seems to work
      score->setNextDifference(level->getRank());

      level->getScores().push_back(std::move(score));
    }
  }
  return levels;
}

std::map<QString, Book *> LoaderMoboberJigger::loadBooks() {
  auto booksJson = loadJson(":/data/books.json").array();
  std::map<QString, Book *> bookMap;
  size_t index = 0;
  for (auto books : booksJson) {
    for (auto bookJson : books.toArray()) {
      auto book = fromJson<Book>(bookJson.toObject());
      book->setIndex(index);
      bookMap[book->getAbbr()] = std::move(book);
    }
    index++;
  }

  return bookMap;
}

Config *LoaderMoboberJigger::loadConfig(QString isoLang) {
  auto defaultConfig = loadJson(":/data/config/default.json");
  auto configJson = loadJson(":/data/config/" + isoLang + ".json");

  auto configObj = configJson.object();
  auto defaultConfigObj = defaultConfig.object();

  for (auto key : defaultConfigObj.keys()) {
    if (configObj.contains(key)) {
      qDebug() << "skipping property " << key;
      continue;
    }
    configObj[key] = defaultConfigObj[key];
  }

  auto config = fromJson<Config>(configObj);

  QStringList list;
  auto versionObj = configObj["version"];
  if (versionObj.isArray()) {
    list = versionObj.toVariant().toStringList();
  } else {
    list.append(versionObj.toString());
    list.append(versionObj.toString());
  }

  config->setVersion(list);
  return std::move(config);
}

Element *LoaderMoboberJigger::loadElement(QString name) {}

QJsonDocument LoaderMoboberJigger::loadJson(QString url) {
  QFile jsonFile(url);
  jsonFile.open(QFile::ReadOnly);
  auto json = QJsonDocument::fromJson(jsonFile.readAll());
  jsonFile.close();
  return json;
}

template <typename T> T *LoaderMoboberJigger::fromJson(QJsonObject jsonObject) {
  static_assert(std::is_base_of<QObject, T>::value,
                "T must inherit from QObject");
  auto fromPtr = new T();
  // auto from = dynamic_cast<QObject *>(fromPtr);
  const auto meta = fromPtr->metaObject();
  int count = meta->propertyCount();
  for (auto i = 0; i < count; i++) {
    auto property = meta->property(i);
    if (jsonObject.contains(property.name())) {
      auto value = jsonObject[property.name()];
      fromPtr->setProperty(property.name(), value.toVariant());
    }
  }
  return std::move(fromPtr);
}

template <typename T>
std::vector<std::unique_ptr<T>> LoaderMoboberJigger::getList(QJsonArray array) {
  auto levels =
      std::vector<std::unique_ptr<T>>(static_cast<size_t>(array.count()));
  size_t index = 0;

  for (auto json : array) {
    levels[index] = std::unique_ptr<T>(fromJson<T>(json.toObject()));
    index++;
  }
  return levels;
}
