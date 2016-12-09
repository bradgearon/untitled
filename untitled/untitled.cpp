#include "untitled.h"

#include <QQuickItem>
#include <QQuickView>
#include <qandroidjnienvironment.h>

#include "jni.h"
#include <QtAndroid>

#include "maincontroller.h"

using namespace untitled;

int untitled_init(int argc, char *argv[]) {
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

  QQuickItem *rootObject = root->rootObject();

#ifdef WIN32
  root->setWidth(800);
  root->setHeight(400);
  root->setPosition(-1360, 340);
#endif

  mainController = new MainController(std::move(rootObject));
  mainController->index();

  const int result = app.exec();

  Q_CLEANUP_RESOURCE(assets);
  return result;
}

void untitled_show() {
  // show the view?
}

void untitled_hide() {
  // hide the view?
}

int Java_com_wds_launcher_OtherActivity_unititled_1works() {
  if (mainController->isReady) {
    mainController->staticMetaObject.invokeMethod(mainController, "show",
                                                  Qt::AutoConnection);
  }
}
