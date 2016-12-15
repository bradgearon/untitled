#include "untitled.h"

#include <QQuickItem>
#include <QQuickView>

#include "maincontroller.h"

#ifdef ANDROID
#include "androidplatformthingee.h"
#endif
#ifdef WIN32
#include "winplatformthingee.h"
#endif

using namespace untitled;

int untitled_init(int argc, char *argv[]) {
  qDebug() << "running ";

  PlatformThingee *platformThingee;

  QByteArray ba;
  int n = 1;
  ba.setNum(n);

  qputenv("QML_IMPORT_TRACE", ba);
  // setup
  QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QQuickStyle::setStyle("Material");
  QQuickWindow::setDefaultAlphaBuffer(true);

  QGuiApplication app(argc, argv);

  QCommandLineParser parser;
  auto gaName = "ga";
  parser.addOptions({
      {{gaName, "google-analytics"},
       "Google analytics account (tracking code)",
       "google analytics"},
  });
  parser.process(app);

  QString ga = "UA-2724338-7";
  if (parser.isSet(gaName)) {
    ga = parser.value(gaName);
  }

  QFontDatabase::addApplicationFont(":/fonts/amiko.ttf");
  QFontDatabase::addApplicationFont(":/fonts/roboto.ttf");

  QFont font("Roboto", 12, QFont::Normal, false);
  app.setFont(font);

#ifdef ANDROID
  platformThingee = new AndroidPlatformThingee();
  platformThingee->hide();
#endif
#ifdef WIN32
  platformThingee = new WinPlatformThingee();
#endif

  Q_INIT_RESOURCE(assets);

  auto root = std::make_unique<QQuickView>();

  root->setResizeMode(QQuickView::SizeRootObjectToView);
  root->setSource(QUrl(QLatin1String("qrc:/main.qml")));

  QQuickItem *rootObject = root->rootObject();
  rootObject->window()->showFullScreen();

#ifdef WIN32
  root->setWidth(800);
  root->setHeight(400);
  root->setPosition(-1360, 340);
#endif

  mainController = new MainController(std::move(rootObject));
  mainController->setPlatformThingee(std::move(platformThingee));
  mainController->setTrackingCode(ga);
  mainController->index();

  const int result = app.exec();

  Q_CLEANUP_RESOURCE(assets);
  return result;
}

void untitled_show() {
  // show
}
