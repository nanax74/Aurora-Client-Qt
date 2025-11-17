#pragma once
#include <memory>
#include <QTcpSocket>
#include "Net/Transport/Connection.hpp"

namespace Net::Transport
{
    class Connector
    {
    public:
        std::shared_ptr<Connection> connectToHost(const QString& ip, quint16 port);
    };
}
