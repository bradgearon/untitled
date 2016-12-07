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

#if ANDROID
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

  QFont roboto("Roboto", 12, QFont::Normal, false);
  app.setFont(roboto);

  auto root = std::make_unique<QQuickView>();

  root->setFlags(Qt::FramelessWindowHint);
  root->setSource(QUrl(QLatin1String("qrc:/main.qml")));

#ifdef WIN32
  root->setWidth(800);
  root->setHeight(400);
  root->setPosition(-1360, 340);
#endif

  LoaderMoboberJigger loader;

  qDebug() << "loading levels ";
  auto levels = loadJson(":/data/level.json");
  LevelPicker picker(loader);

  auto locale = QLocale::system();
  auto isoLang = locale.name().split("_")[0];

  auto cultures = loadJson(":/data/culture.json");
  auto culture = cultures.object()[isoLang];

  // read /:id/:version
  qDebug() << culture << " for lang " << isoLang << " " << locale;

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

  // books obj used for to get version and build learn more url
  // it uses config

  //

  auto config = loader.loadConfig("he");
  auto scoreThingee = std::make_unique<ScoreThingee>(&picker);

  scoreThingee->readScores();
  scoreThingee->saveScores();

  auto picked = picker.pick();
  auto parts = picked->getName().split('-');

  QString version;
  auto versionObj = config->getVersion();
  if (versionObj.canConvert(QVariant::StringList)) {
    auto index = bookMap[parts[0]]->getIndex();
    // parts[0] is the Book // get the order from the map
    versionObj.convert(QVariant::StringList);
    version = versionObj.toList()[index].toString();
  } else {
    version = versionObj.toString();
  }

  bool isRtl = config->getRtl();
  qDebug() << "rtl: " << isRtl;

  auto path = ":/data/word/" + picked->getName() + "/" + version + ".json";
  auto imagePath = "images/" + picked->getName() + ".jpg";

  auto testModel = loadJson(path);

  // controller:
  auto viewModel = std::make_unique<Form1ViewModel>(testModel.object());

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
