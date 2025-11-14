#include "ConsoleController.hpp"
#include <QDebug>

ConsoleController::ConsoleController(QObject* parent) : QObject(parent), m_process(new QProcess(this)), m_model(new ConsoleModel(this))
{
    m_process->setProcessChannelMode(QProcess::MergedChannels);
    connect(m_process, &QProcess::readyRead, this, &ConsoleController::onReadyRead);
}

void ConsoleController::startProcess(const QString& exePath)
{
    if (m_process->state() != QProcess::NotRunning)
    {
        m_process->terminate();
        m_process->waitForFinished(1000);
    }

    m_process->start(exePath);
    if (!m_process->waitForStarted(1000))
    {
        qWarning() << "Failed to start process:" << exePath;
    }
}

void ConsoleController::sendCommand(const QString& cmd)
{
    if (m_process->state() == QProcess::Running)
    {
        m_process->write((cmd + "\n").toUtf8());
    }
}

void ConsoleController::onReadyRead()
{
    const QByteArray data = m_process->readAll();
    const QString text = QString::fromLocal8Bit(data);
    m_model->appendLine(text);
}
