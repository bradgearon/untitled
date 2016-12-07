#include "untitled.h"

#include <QQuickItem>
#include <future>
#include <qquickview.h>

#include "models.h"

#include "form1viewmodel.h"
#include "languagethingee.h"
#include "levelpicker.h"
#include "loadermoboberjigger.h"
#include "scorethingee.h"

using namespace untitled;

// static JavaVM *g_VM;

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

int untitled_start(int argc, char *argv[]) {

  qDebug() << "running ";
  Q_INIT_RESOURCE(assets);
  QByteArray ba;
  int n = 1;
  ba.setNum(n);
  qputenv("QML_IMPORT_TRACE", ba);
// JNI_OnLoad

#ifdef ANDROID
// QLibrary platform("libplugins_platforms_android_libqtforandroid");

// QFileInfo platformFile(platform.fileName());
// auto pluginPath = platformFile.absolutePath();
// qputenv("QT_QPA_PLATFORM_PLUGIN_PATH", pluginPath.toUtf8());
// qDebug() << "QT_QPA_PLATFORM_PLUGIN_PATH: " << pluginPath;
#endif

  // setup
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QQuickStyle::setStyle("Material");
  QQuickWindow::setDefaultAlphaBuffer(true);

  QGuiApplication app(argc, argv);

  QFontDatabase::addApplicationFont(":/fonts/amiko.ttf");
  QFontDatabase::addApplicationFont(":/fonts/roboto.ttf");

  QFont font("Roboto", 12, QFont::Normal, false);
  app.setFont(font);

  auto root = std::make_unique<QQuickView>();

  root->setFlags(Qt::FramelessWindowHint);
  root->setSource(QUrl(QLatin1String("qrc:/main.qml")));

#ifdef WIN32
  root->setWidth(800);
  root->setHeight(400);
  root->setPosition(-1360, 340);
#endif

  LoaderMoboberJigger loader;

  LevelPicker picker(loader);
  LanguageThingee thingee(loader);

  auto bookMap = loader.loadBooks();

  auto locale = QLocale::system();
  auto isoLang = locale.name().split("_")[0];

  auto config = loader.loadConfig(isoLang);

  // books obj used for to get version and build learn more url
  // it uses config

  auto scoreThingee = std::make_unique<ScoreThingee>(&picker);

  scoreThingee->readScores();
  scoreThingee->saveScores();

  auto picked = picker.pick();

  auto versionObj = config->getVersion();
  auto parts = picked->getName().split('-');
  int index = static_cast<int>(bookMap[parts[0]]->getIndex());
  QString version = versionObj[index];

  auto path = ":/data/word/" + picked->getName() + "/" + version + ".json";
  auto imagePath = "images/" + picked->getName() + ".jpg";

  auto isRtl = config->getRtl();
  auto more = config->getMore();

  auto testModel = loadJson(path);

  // controller:
  auto viewModel = std::make_unique<Form1ViewModel>(testModel.object());

  viewModel->setMore(more);
  viewModel->setIsRtl(isRtl);
  viewModel->setImageName(imagePath);
  viewModel->setScore(picked);

  QObject::connect(viewModel.get(), &Form1ViewModel::close, [&root] {
    root->hide();
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(5s);
    root->show();
  });

  QObject::connect(picked, &Score::readChanged,
                   [&scoreThingee] { scoreThingee->saveScores(); });

  QObject::connect(viewModel.get(), &Form1ViewModel::ready, [&root] {
    qDebug() << "on show from untitled";
    root->show();
  });

  QObject::connect(viewModel.get(), &Form1ViewModel::read, [&](auto value) {
    qDebug() << "on read from untitled " << value;
  });

  QObject::connect(viewModel.get(), &Form1ViewModel::learnMore,
                   [&] { qDebug() << "on learn more from untitled"; });

  QQuickItem *rootObject = root->rootObject();
  rootObject->setProperty("model", QVariant::fromValue(viewModel.get()));

  const int result = app.exec();
  Q_CLEANUP_RESOURCE(assets);
  return result;
}
