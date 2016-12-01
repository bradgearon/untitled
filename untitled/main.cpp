#include <QDebug>
#include <QDesktopServices>
#include <QFile>
#include <QGuiApplication>
#include <QJsonDocument>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QWindow>
#include <QtCore>
#include <functional>

#include "levelpicker.h"
#include <QtSql>

QJsonObject getCookieValue() {

  auto dbPath =
#ifndef WIN32
      QFileInfo(QDir::currentPath()).dir().absolutePath() + "/" +
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

void readCookies(LevelPicker picker) {
  QSaveFile readFile("read.dat");
  readFile.open(QIODevice::WriteOnly);
  QDataStream readStream(&readFile);

  auto cookieValue = getCookieValue();
  auto keys = cookieValue.keys();
  for (auto key : keys) {
    auto read = cookieValue[key].toObject();
    auto value = read["value"];
    readStream << key << value.toDouble();

    picker.setRead(key, value.toDouble());
  }

  readFile.commit();
}

void readSaveFile(LevelPicker picker) {
  QFile readFile("read.dat");
  readFile.open(QIODevice::ReadOnly);
  QDataStream read(&readFile);
  QString name;
  double value;
  while (!read.atEnd()) {
    read >> name;
    read >> value;
    qDebug() << "name " << name << " value " << value;

    picker.setRead(name, value);
  }

  readFile.close();
}

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QQuickStyle::setStyle("Material");
  QQmlApplicationEngine engine;

  engine.load(QUrl(QLatin1String("qrc:/main.qml")));

  QWindow *root = qobject_cast<QWindow *>(engine.rootObjects().first());

// root->setWindowState(Qt::WindowState::WindowFullScreen);

#if WIN32
  root->setWidth(800);
  root->setHeight(400);
  root->setPosition(-1360, 340);
#endif

  QFile levelJson(":/data/level.json");
  levelJson.open(QFile::ReadOnly);
  auto json = QJsonDocument::fromJson(levelJson.readAll());
  levelJson.close();

  LevelPicker picker(json.array());

  auto locale = QLocale::system();
  auto isoLang = locale.name().split("_")[0];

  QFile testJson(":/test.json");
  testJson.open(QFile::ReadOnly);
  json = QJsonDocument::fromJson(testJson.readAll());
  testJson.close();

  auto model = json.toVariant();
  root->setProperty("model", model);

  readCookies(picker);
  readSaveFile(picker);

  picker.setRead("testing", 123);

  return app.exec();
}

void testPicker(LevelPicker picker) {
  picker.setRead("Gen-1-1", .5);
  picker.setRead("Mat-19-16", 1);
  picker.setRead("Luk-2-8", 1);
  picker.setRead("Mat-6-19", 1);
  picker.setRead("Acts-2-1", 1);

  for (int i = 0; i < 100; i++) {
    Score *picked = picker.pick();

    qDebug() << " picked: " << picked->getName() << " " << picked->getWeight()
             << " " << picked->getRank();
  }
}
