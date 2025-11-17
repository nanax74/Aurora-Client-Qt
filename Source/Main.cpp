#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Net/Transport/Client.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    auto client = new Net::Transport::Client();

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("client", client);

    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));
    if (engine.rootObjects().isEmpty()) return -1;

    return app.exec();
}
