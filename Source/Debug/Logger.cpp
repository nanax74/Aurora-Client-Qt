#include "Debug/Logger.hpp"
#include <QDebug>

namespace Debug
{
    bool Logger::init()
    {
        isEnabled = true;
        return true;
    }

    bool Logger::shutdown()
    {
        isEnabled = false;
        return true;
    }

    bool Logger::write(const std::string& msg)
    {
        qDebug() << msg;
        return true;
    }
}
