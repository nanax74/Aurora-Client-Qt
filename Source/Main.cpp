#include <QGuiApplication>
#include <QQmlApplicationEngine>


#include "ConsoleController.hpp"
#include "ConsoleModel.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<ConsoleController>("Aurora", 1, 0, "ConsoleController");
    qmlRegisterType<ConsoleModel>("Aurora", 1, 0, "ConsoleModel");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl)
    {
        if (!obj && url == objUrl) QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
