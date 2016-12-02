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
#include "scorethingee.h"

void testPicker(LevelPicker *picker, ScoreThingee *scores) {
  picker->setRead("Gen-1-1", .5);
  picker->setRead("Mat-19-16", 1);
  picker->setRead("Luk-2-8", 1);
  picker->setRead("Mat-6-19", 1);
  picker->setRead("Acts-2-1", 1);

  for (int i = 0; i < 10000; i++) {
    Score *picked = picker->pick();

    qDebug() << " picked: " << picked->getName() << " " << picked->getWeight()
             << " " << picked->getRank();

    qDebug() << "before: " << time(0);
    scores->saveScores();
    qDebug() << "after: " << time(0);
  }
}

int main(int argc, char *argv[]) {
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QQuickStyle::setStyle("Material");

  QGuiApplication app(argc, argv);
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

  ScoreThingee scoreThingee = ScoreThingee(&picker);

  scoreThingee.readScores();
  scoreThingee.saveScores();

  picker.setRead("testing", 123);
  testPicker(&picker, &scoreThingee);

  return app.exec();
}
