#include <QDebug>
#include <QDesktopServices>
#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QWindow>
#include <QtCore>
#include <functional>

#include "levelpicker.h"
#include "scorethingee.h"

using namespace untitled;

void testPicker(LevelPicker *picker, ScoreThingee *scores) {
  picker->setRead("Gen-1-1", .5);
  picker->setRead("Mat-19-16", 1);
  picker->setRead("Luk-2-8", 1);
  picker->setRead("Mat-6-19", 1);
  picker->setRead("Acts-2-1", 1);

  for (int i = 0; i < 100; i++) {
    auto picked = picker->pick();

    qDebug() << " picked: " << picked->getName() << " " << picked->getWeight()
             << " " << picked->getRank();

    qDebug() << "before: " << time(0);
    scores->saveScores();
    qDebug() << "after: " << time(0);
  }
}

QJsonDocument loadJson(QString path) {
  QFile jsonFile(path);
  jsonFile.open(QFile::ReadOnly);
  auto json = QJsonDocument::fromJson(jsonFile.readAll());
  jsonFile.close();
  return json;
}

int main(int argc, char *argv[]) {
  Q_INIT_RESOURCE(assets);

  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QQuickStyle::setStyle("Material");

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  int id = QFontDatabase::addApplicationFont(":/fonts/amiko.ttf");
  QFontDatabase::addApplicationFont(":/fonts/roboto.ttf");
  QFontDatabase::addApplicationFont(":/fonts/opensans.ttf");
  QString family = QFontDatabase::applicationFontFamilies(id).at(0);
  qDebug() << "font: " << family;

  engine.load(QUrl(QLatin1String("qrc:/main.qml")));

  QWindow *root = qobject_cast<QWindow *>(engine.rootObjects().first());

// root->setWindowState(Qt::WindowState::WindowFullScreen);

#ifdef WIN32
  root->setWidth(800);
  root->setHeight(400);
  root->setPosition(-1360, 340);
#endif

  auto levels = loadJson(":/data/level.json");
  LevelPicker picker(levels.array());

  auto locale = QLocale::system();
  auto isoLang = locale.name().split("_")[0];

  auto cultures = loadJson(":/data/culture.json");
  auto culture = cultures.object()[isoLang];

  isoLang = "ar";
  qDebug() << culture;

  auto books = loadJson(":/data/books.json").array();
  auto bookMap = std::map<QString, Book *>();

  for (uchar index = 0; index < books.count(); index++) {
    auto list = books[index].toArray();
    for (auto book : list) {
      auto bookObj = book.toObject();
      Book bookModel(0);

      bookModel.setIndex(index);
      bookModel.setAbbr(bookObj["abbr"].toString());
      bookModel.setName(bookObj["name"].toString());
      bookModel.setOrder(bookObj["ord"].toString());

      bookMap[bookModel.getAbbr()] = &bookModel;

      qDebug() << bookModel.getAbbr() << " " << bookModel.getName() << " "
               << bookModel.getIndex() << " " << bookModel.getOrder();
    }
  }

  auto defaultConfig = loadJson(":/data/config/default.json");
  auto config = loadJson(":/data/config/" + isoLang + ".json");
  bool isRtl = config.object()["rtl"].toBool();

  auto configObj = config.object();
  auto defaultConfigObj = defaultConfig.object();

  for (auto key : defaultConfigObj.keys()) {
    if (configObj.contains(key)) {
      qDebug() << "skipping property " << key;
      continue;
    }
    configObj[key] = defaultConfigObj[key];
  }

  auto scoreThingee = std::make_unique<ScoreThingee>(&picker);

  scoreThingee->readScores();
  scoreThingee->saveScores();

  auto picked = picker.pick();
  auto parts = picked->getName().split('-');

  QString version;
  auto versionObj = configObj["version"];
  if (versionObj.isArray()) {
    // parts[0] is the Book // get the order from the map
    version = versionObj.toArray()[bookMap[parts[0]]->getIndex()].toString();
  } else {
    version = versionObj.toString();
  }

  auto path = ":/data/word/" + picked->getName() + "/" + version + ".json";
  auto imagePath = "images/" + picked->getName() + ".jpg";

  auto testModel = loadJson(path);

  auto testObject = testModel.object();
  testObject["imageName"] = imagePath;
  testObject["isRtl"] = isRtl;
  root->setProperty("model", testObject.toVariantMap());

  Q_CLEANUP_RESOURCE(assets);
  return app.exec();
}
