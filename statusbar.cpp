#include "statusbar.h"
#include <QSerialPortInfo>
#include <QString>
#include <QtSerialPort/QtSerialPort>

StatusBar::StatusBar(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
}

void StatusBar::sessionChanged(const Settings::Session &session)
{
    QString parity;
    switch (session.parity) {
    case QSerialPort::NoParity:
        parity = QStringLiteral("N");
        break;
    case QSerialPort::MarkParity:
        parity = QStringLiteral("Mark");
        break;
    case QSerialPort::SpaceParity:
        parity = QStringLiteral("Space");
        break;
    case QSerialPort::EvenParity:
        parity = QStringLiteral("Even");
        break;
    case QSerialPort::OddParity:
        parity = QStringLiteral("Odd");
        break;
    default:
        parity = QStringLiteral("?");
        break;
    }
    QString stopBits;
    switch (session.stopBits) {
    case QSerialPort::OneStop:
        stopBits = QString::number(1);
        break;
    case QSerialPort::OneAndHalfStop:
        stopBits = QString::number(1.5);
        break;
    case QSerialPort::TwoStop:
        stopBits = QString::number(2);
        break;
    default:
        break;
    }

    QString connectionParameter
        = QString("%1 @ %2-%3-%4").arg(session.baudRate).arg(session.dataBits).arg(parity).arg(stopBits);
    m_lb_portparams->setText(connectionParameter);

    if (!session.device.isEmpty())
        m_lb_deviceName->setText(session.device);
    QWidget::setToolTip(QStringLiteral(""));
}

void StatusBar::setDeviceInfo(const QSerialPort *port)
{
    QSerialPortInfo info = QSerialPortInfo(*port);
    if (info.isValid()) {
        QString deviceInfo = QString("%1 %2 @%3").arg(info.manufacturer()).arg(info.description()).arg(info.portName());
        m_lb_deviceName->setText(deviceInfo);
    }
}

void StatusBar::setToolTip(const QSerialPort *port)
{

    QSerialPortInfo info = QSerialPortInfo(*port);
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
        QWidget::setToolTip(deviceInfo);
    } else {
        QWidget::setToolTip(tr("Not a valid device"));
    }
}
