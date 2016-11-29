#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWindow>
#include <QJsonDocument>
#include <QFile>
#include <QDesktopServices>
#include <QDebug>
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

    for(auto level: picker.getLevels()) {
        qDebug() << "level: " << level->getRank();
    }

    QWindow *root = qobject_cast<QWindow *>(
                engine.rootObjects().first());

    root->setProperty("model",  model);

    // pick an element:
    // pick a level
    //



    return app.exec();
}
