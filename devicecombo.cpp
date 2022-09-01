#include "devicecombo.h"

#include "qdebug.h"
#include <QSerialPortInfo>

void DeviceCombo::showPopup()
{
    refill();
    QComboBox::showPopup();
}

void DeviceCombo::refill()
{
    QString selection = currentText();
    clear();
    int numberDevices = 0;
    for (auto info : QSerialPortInfo::availablePorts()) {
#ifdef Q_OS_WIN
        addItem(info.portName());
#else
        addItem(info.systemLocation());
#endif
        if (info.isValid()) {
            QString deviceInfo = QString("%1 %2\n%3:%4 "
#if QT_VERSION < QT_VERSION_CHECK(5, 3, 0)
                                         )
#else
                                         "# %5")
#endif
                                     .arg(info.manufacturer())
                                     .arg(info.description())
                                     .arg(info.vendorIdentifier())
                                     .arg(info.productIdentifier())
#if QT_VERSION < QT_VERSION_CHECK(5, 3, 0)
                ;
#else
                                     .arg(info.serialNumber());
#endif
            setItemData(numberDevices, deviceInfo, Qt::ToolTipRole);
        } else {
            setItemData(numberDevices, tr("Not a valid device"), Qt::ToolTipRole);
        }
        numberDevices++;
    }

    int index = findText(selection);
    if (index != -1) {
        // found something - work done!
        setCurrentIndex(index);
    } else {
        // maybe it's no longer connected
        // ToDo add this in a different colour
        // via a own model to indicate the
        // device's absence
        // add this to the list and select this anyway as
        // the user might want to reconnect the device
        // after reconnection the device will be shown in the
        // error/unconnected colour since we will get no notification
        // about devices beeing removed or attached
        // which is our problem in the first place
        addItem(selection);
        setCurrentIndex(numberDevices);
    }
}
