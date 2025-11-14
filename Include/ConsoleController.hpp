#pragma once
#include <QObject>
#include <QProcess>
#include "ConsoleModel.hpp"

class ConsoleModel;

class ConsoleController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ConsoleModel* model READ model CONSTANT)

public:
    explicit ConsoleController(QObject* parent = nullptr);

    ConsoleModel* model() const { return m_model; }

    Q_INVOKABLE void startProcess(const QString& exePath);
    Q_INVOKABLE void sendCommand(const QString& cmd);

private slots:
    void onReadyRead();

private:
    QProcess* m_process;
    ConsoleModel* m_model;
};
