#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QWindow>
#include <QJsonDocument>
#include <QFile>

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

    QWindow *root = qobject_cast<QWindow *>(
                engine.rootObjects().first());


    root->setProperty("model",  json.toVariant());

    return app.exec();
}
