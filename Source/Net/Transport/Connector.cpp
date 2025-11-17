#include "Net/Transport/Connector.hpp"
#include <QAbstractSocket>

namespace Net::Transport
{
    std::shared_ptr<Connection> Connector::connectToHost(const QString& ip, quint16 port)
    {
        auto socket = std::make_shared<QTcpSocket>();
        socket->setSocketOption(QAbstractSocket::LowDelayOption, 1);
        auto connection = std::make_shared<Connection>(socket);
        
        socket->connectToHost(ip, port);
        
        return connection;
    }
}
