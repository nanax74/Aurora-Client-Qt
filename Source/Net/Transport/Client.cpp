#include "Net/Transport/Client.hpp"
#include "Data/ByteReader.hpp"
#include "Net/Transport/Connector.hpp"
#include "qstringview.h"
#include <QDebug>

namespace Net::Transport
{
    Client::Client(QObject* parent) : QObject(parent) {}

    void Client::connectToHost(const QString& ip, quint16 port)
    {
        Connector connector;
        connection = connector.connectToHost(ip, port);

        connect(connection.get(), &Connection::received, this, &Client::received);
        connect(connection.get(), &Connection::disconnected, this, &Client::disconnected);

        connect(this, &Client::received, this, &Client::onReceived);
    }

    void Client::disconnect()
    {
        if (connection && connection->getSocket()->isOpen()) connection->getSocket()->disconnectFromHost();
    }

    bool Client::send(std::unique_ptr<Protocol::IData> data)
    {
        if (!connection || !connection->getSocket()->isOpen()) return false;
        return connection->send(std::move(data)) > 0;
    }

    void Client::onReceived(const QByteArray data)
    {
        std::vector<std::byte> vec(
            reinterpret_cast<const std::byte*>(data.constData()),
            reinterpret_cast<const std::byte*>(data.constData() + data.size())
        );
        Data::ByteReader reader(vec);
        Protocol::ID id = reader.read<Protocol::ID>();
        std::vector<std::byte> payload = reader.readBytes(reader.remain());
        auto protocolData = std::unique_ptr<Protocol::IData>(registry.deserialize(id, payload));
        if (protocolData) protocolData->process(connection);
    }
}
