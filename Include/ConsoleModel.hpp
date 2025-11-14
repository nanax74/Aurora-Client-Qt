#pragma once
#include <QAbstractListModel>
#include <QStringList>

class ConsoleModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles
    {
        TextRole = Qt::UserRole + 1
    };

    explicit ConsoleModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void appendLine(const QString& line);

private:
    QStringList m_lines;
};
