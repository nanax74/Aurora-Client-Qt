#pragma once
#include <QObject>
#include <memory>
#include "Net/Transport/Connection.hpp"
#include "Net/Protocol/Registry.hpp"
#include "qstringview.h"
#include "qtmetamacros.h"

namespace Net::Transport
{
    class Client : public QObject
    {
        Q_OBJECT
    public:
        explicit Client(QObject* parent = nullptr);

        Q_INVOKABLE void connectToHost(const QString& ip, quint16 port);
        Q_INVOKABLE void disconnect();

        bool send(std::unique_ptr<Protocol::IData> data);

    signals:
        void received(QByteArray data);
        void disconnected();

    private slots:
        void onReceived(const QByteArray data);

    private:
        std::shared_ptr<Connection> connection;
        Protocol::Registry registry;
    };
}
