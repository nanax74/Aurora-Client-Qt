#include "Handler.hpp"
#include <QTcpSocket>
#include <QDebug>

Handler::Handler(QTcpSocket& socket, QObject* parent) : QObject(parent), socket(socket) {}

void Handler::handleButtonClick()
{
    socket.write("Button is clicked!");
    qDebug() << "Button is clicked!";
}
