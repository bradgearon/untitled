#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWindow>
#include <QJsonDocument>
#include <QFile>
#include <QDesktopServices>
#include <QDebug>
#include <functional>

#include "levelpicker.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    QFile testJson(":/test.json");
    testJson.open(QFile::ReadOnly);
    auto json = QJsonDocument::fromJson(testJson.readAll());
    testJson.close();
    auto model = json.toVariant();

    QFile levelJson(":/level.json");
    levelJson.open(QFile::ReadOnly);
    json = QJsonDocument::fromJson(levelJson.readAll());
    levelJson.close();
    LevelPicker picker(json.array());

    // picker.setRead("Gen-1-1", 1);


    QWindow *root = qobject_cast<QWindow *>(
                engine.rootObjects().first());

    root->setProperty("model",  model);

    root->setWidth(800);
    root->setHeight(400);

    // pick an element:
    // pick a level
    //



    return app.exec();
}
