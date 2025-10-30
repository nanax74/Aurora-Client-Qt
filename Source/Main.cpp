#include "Handler.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTcpSocket>
#include <QTimer>
#include <QQmlContext>

QTcpSocket socket;
Handler* handler;

void socketTest(QGuiApplication &app, QQmlApplicationEngine &engine)
{
    QObject::connect(&socket, &QTcpSocket::connected, [&]()
    {
        qDebug() << "Connected to server";
        socket.write("Hello Server!");
    });

    QObject::connect(&socket, &QTcpSocket::readyRead, [&]()
    {
        qDebug() << "Received from server:" << socket.readAll();
    });

    QObject::connect(&socket, &QTcpSocket::errorOccurred, [&](QAbstractSocket::SocketError error)
    {
        qDebug() << "Error:" << socket.errorString();
    });

    socket.connectToHost("192.168.68.201", 55555);

    handler = new Handler(socket, &app);
    engine.rootContext()->setContextProperty("handler", handler);
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    socketTest(app, engine);

    engine.load(QUrl(QStringLiteral("qrc:/Main.qml")));
    if (engine.rootObjects().isEmpty()) return -1;
    return app.exec();
}
