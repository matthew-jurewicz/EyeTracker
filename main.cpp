#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "messagedialog.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    MessageDialog *msg = new MessageDialog;

    return app.exec();
}
