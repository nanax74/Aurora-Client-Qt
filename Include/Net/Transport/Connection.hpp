#pragma once
#include <QObject>
#include <QTcpSocket>
#include <memory>
#include <vector>
#include "Net/Protocol/IData.hpp"

namespace Net::Transport
{
    class Connection : public QObject
    {
        Q_OBJECT
    public:
        explicit Connection(std::shared_ptr<QTcpSocket> socket, QObject* parent = nullptr);

        qint64 send(std::unique_ptr<Protocol::IData> data);
        std::shared_ptr<QTcpSocket> getSocket() const { return socket; }

    signals:
        void received(QByteArray data);
        void disconnected();
        void errorOccurred(const QString& msg);

    private slots:
        void onReadyRead();
        void onDisconnected();
        void onError(QAbstractSocket::SocketError socketError);

    private:
        std::shared_ptr<QTcpSocket> socket;
    };
}
