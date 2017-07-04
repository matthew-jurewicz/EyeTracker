#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "streammanager.h"
#include "messagedialog.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MessageDialog *message = new MessageDialog;
    StreamManager *manager = new StreamManager(this);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
