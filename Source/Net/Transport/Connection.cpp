#include "Net/Transport/Connection.hpp"
#include <QDebug>

namespace Net::Transport
{
    Connection::Connection(std::shared_ptr<QTcpSocket> s, QObject* parent) : QObject(parent), socket(s)
    {
        connect(socket.get(), &QTcpSocket::readyRead, this, &Connection::onReadyRead);
        connect(socket.get(), &QTcpSocket::disconnected, this, &Connection::onDisconnected);
        connect(socket.get(), &QTcpSocket::errorOccurred, this, &Connection::onError);
    }

    qint64 Connection::send(std::unique_ptr<Protocol::IData> data)
    {
        auto vec = data->serialize();
        QByteArray array(reinterpret_cast<const char*>(vec.data()), static_cast<int>(vec.size()));
        return socket->write(array);
    }

    void Connection::onReadyRead()
    {
        QByteArray data = socket->readAll();
        emit received(data);
    }

    void Connection::onDisconnected() { emit disconnected(); }

    void Connection::onError(QAbstractSocket::SocketError)
    {
        emit errorOccurred(socket->errorString());
    }
}
