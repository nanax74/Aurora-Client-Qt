#pragma once

#include <QObject>
#include <QTcpSocket>

class Handler : public QObject
{
    Q_OBJECT
private:
    QTcpSocket& socket;

public:
    explicit Handler(QTcpSocket& socket, QObject* parent = nullptr);

    Q_INVOKABLE void handleButtonClick();
};
