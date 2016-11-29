#include "main.h"
#include "pageaction.h"

void hello() {
    std::this_thread::sleep_for(std::chrono::seconds(10));
    qDebug("here I is, rock you like a hurricane!");
    // view->hide();
    return;
}

void extract(QString web) {
    QuaZip webZip(":/web.zip");
    if(!webZip.open(QuaZip::mdUnzip)) {
        return;
    }

    int chunkSize = 1024;
    QByteArray buffer;
    QuaZipFile source(&webZip);
    QFileInfo info;

    for(bool f = webZip.goToFirstFile(); f; f = webZip.goToNextFile()) {
        source.open(QIODevice::ReadOnly);
        auto path = web + source.getActualFileName();
        QFile destination(path);

        auto dir = QFileInfo(destination).absoluteDir();
        dir.mkpath(dir.absolutePath());

        destination.open(QIODevice::WriteOnly);
        while(!(buffer = source.read(chunkSize)).isEmpty()) {
            destination.write(buffer);
        }

        source.close();
        destination.close();
    }

    webZip.close();
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    auto dataLocation = QStandardPaths::standardLocations(
                QStandardPaths::DataLocation)[0];
    auto web = dataLocation + "/web/";

    extract(web);

    QtWebView::initialize();

    QString local = web + "index.html";
    QString initialUrlName = "initialUrl";
    QUrl initialUrl = QUrl::fromLocalFile(local);

    QQmlApplicationEngine engine(QUrl("qrc:/main.qml"));

    engine.rootContext()
            ->setContextProperty(initialUrlName, initialUrl.toString());

    PageAction viewModel;

    // engine. rootContext()
        //    ->setContextProperty("viewModel",  &viewModel);

    QWindow *root = qobject_cast<QWindow *>(
                engine.rootObjects().first());

    root->setProperty("viewModel", QVariant::fromValue(&viewModel));

    root->setVisibility(QWindow::Windowed);
    root->setGeometry(0, 0, 480, 640);
    root->show();

    // detect read more and launch intent
    // detect close and hide the activity

    return app.exec();
}

