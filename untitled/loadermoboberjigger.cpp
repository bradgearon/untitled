#include "loadermoboberjigger.h"
using namespace untitled;

LoaderMoboberJigger::LoaderMoboberJigger() {}

std::vector<std::unique_ptr<Level>> LoaderMoboberJigger::loadLevels() {
  auto levelsJson = loadJson(":/data/level.json").array();
  auto levels = getList<Level>(levelsJson);
  for (size_t i = 0; i < levels.size(); i++) {
    auto elements =
        levelsJson[static_cast<int>(i)].toObject()["elements"].toArray();
    for (auto element : elements) {
      auto level = levels[i].get();
      auto score = std::make_unique<Score>(level);

      // double nextDifference = getRank() - nextRank;
      // todo: connect Score::onValueUpdated to updateWhateverItis
      score->setName(element.toString());
      score->setRank(level->getRank());
      score->setWeight(level->getRank());
      score->setNextDifference(0); // todo: nextDifference

      levels[i]->getScores().push_back(std::move(score));
    }
  }
  return levels;
}

std::vector<std::unique_ptr<Book>> LoaderMoboberJigger::loadBooks() {
  auto booksJson = loadJson(":/data/books.json").array();
  return getList<Book>(booksJson);
}

Config *LoaderMoboberJigger::loadConfig(QString isoLang) {
  auto defaultConfig = loadJson(":/data/config/default.json");
  auto config = loadJson(":/data/config/" + isoLang + ".json");

  auto configObj = config.object();
  auto defaultConfigObj = defaultConfig.object();

  for (auto key : defaultConfigObj.keys()) {
    if (configObj.contains(key)) {
      qDebug() << "skipping property " << key;
      continue;
    }
    configObj[key] = defaultConfigObj[key];
  }

  return fromJson<Config>(configObj);
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
  auto from = dynamic_cast<QObject *>(fromPtr);
  const auto meta = from->metaObject();
  int count = meta->propertyCount();
  for (auto i = 0; i < count; i++) {
    auto property = meta->property(i);
    if (jsonObject.contains(property.name())) {
      auto value = jsonObject[property.name()];
      from->setProperty(property.name(), value.toVariant());
    }
  }
  return fromPtr;
}

template <typename T>
std::vector<std::unique_ptr<T>> LoaderMoboberJigger::getList(QJsonArray array) {
  auto levels =
      std::vector<std::unique_ptr<T>>(static_cast<size_t>(array.count()));
  size_t index = 0;

  for (auto json : array) {
    auto level = fromJson<T>(json.toObject());
    levels[index] = std::unique_ptr<T>(level);
    index++;
  }
  return levels;
}
