#include "serialdevicelistmodel.h"

#include "qdebug.h"
#include <QSerialPortInfo>

SerialDeviceListModel::SerialDeviceListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int SerialDeviceListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    qDebug() << Q_FUNC_INFO;
    return m_device_count;
}

QVariant SerialDeviceListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_devices.size() || index.row() < 0)
        return QVariant();

    qDebug() << Q_FUNC_INFO;
    if (role == Qt::ToolTipRole) {
        return QStringLiteral("SerialDevice ...");
    } else if (role == Qt::DisplayRole) {
        return m_devices.at(index.row());
    } else {
        return QVariant();
    }
}

bool SerialDeviceListModel::canFetchMore(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    qDebug() << Q_FUNC_INFO;
    return true;
}

void SerialDeviceListModel::fetchMore(const QModelIndex &parent)
{
    Q_UNUSED(parent)
    m_devices.clear();
    for (auto info : QSerialPortInfo::availablePorts()) {
#ifdef Q_OS_WIN
        m_devices.append(info.portName());
#else
        m_devices.append(info.systemLocation());
#endif
    }
    m_device_count = m_devices.size();
}
