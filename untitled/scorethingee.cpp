#include "scorethingee.h"

ScoreThingee::ScoreThingee(LevelPicker *picker) {
  this->picker = picker;
  saveFile = std::make_unique<QSaveFile>("read.dat");
}

QJsonObject ScoreThingee::getCookieValue() {
  auto dbPath =
#ifdef WIN32
      QCoreApplication::applicationDirPath() + "/" +
#endif
      "app_webview/Cookies";

  qDebug() << dbPath;
  auto db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(dbPath);

  if (!db.open()) {
    qDebug() << "error connecting ";
  }

  auto query =
      db.exec(QString("select value from cookies where name = 'read'"));

  QJsonObject valueJson;
  QString value;

  if (query.first()) {
    auto valueBytes = query.value("value").toByteArray();
    value = QUrl::fromPercentEncoding(valueBytes).remove(QChar('\\'));

    valueJson = QJsonDocument::fromJson(value.toUtf8()).object();
  }

  db.close();
  return valueJson;
}

void ScoreThingee::readCookie() {
  auto cookieValue = getCookieValue();
  auto keys = cookieValue.keys();
  for (auto key : keys) {
    auto read = cookieValue[key].toObject();
    auto value = read["value"];
    picker->setRead(key, value.toDouble());
  }
}

void ScoreThingee::readSave() {
  QFile readFile("read.dat");
  readFile.open(QIODevice::ReadOnly);
  QDataStream read(&readFile);
  QString name;
  double value;
  while (!read.atEnd()) {
    read >> name;
    read >> value;
    qDebug() << "name " << name << " value " << value;
    picker->setRead(name, value);
  }

  readFile.close();
}

void ScoreThingee::readScores() {
  readCookie();
  readSave();
}

void ScoreThingee::saveScores() {
  saveFile->open(QIODevice::WriteOnly);
  QDataStream saveStream(saveFile.get());

  for (auto pair : picker->getScoreMap()) {
    Score *score = pair.second;
    double read = score->getRead();
    if (read > 0) {
      saveStream << score->getName() << read;
    }
  }
  saveFile->commit();
  qDebug() << "saving scores";
}
