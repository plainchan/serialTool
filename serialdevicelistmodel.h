#ifndef SERIALDEVICELISTMODEL_H
#define SERIALDEVICELISTMODEL_H

#include <QAbstractListModel>

class SerialDeviceListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SerialDeviceListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

protected:
    bool canFetchMore(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    void fetchMore(const QModelIndex &parent) Q_DECL_OVERRIDE;

private:
    QStringList m_devices;
    int m_device_count;
};

#endif // SERIALDEVICELISTMODEL_H
