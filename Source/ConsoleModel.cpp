#include "ConsoleModel.hpp"

ConsoleModel::ConsoleModel(QObject* parent) : QAbstractListModel(parent)
{

}

int ConsoleModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : m_lines.size();
}

QVariant ConsoleModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != TextRole) return {};

    return m_lines[index.row()];
}

QHash<int, QByteArray> ConsoleModel::roleNames() const
{
    return
    {
        { TextRole, "text" }
    };
}

void ConsoleModel::appendLine(const QString& text)
{
    if (text.isEmpty()) return;

    const QStringList lines = text.split('\n');

    beginInsertRows(QModelIndex(), rowCount(), rowCount() + lines.size() - 1);
    for (const QString& line : lines)
    {
        if (!line.isEmpty()) m_lines.append(line);
    }
    endInsertRows();
}
