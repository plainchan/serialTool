#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "settings.h"
#include "ui_statusbar.h"

class StatusBar : public QWidget, private Ui::StatusBar
{
    Q_OBJECT

public:
    explicit StatusBar(QWidget *parent = nullptr);
    void sessionChanged(const Settings::Session &session);
    void setDeviceInfo(const QSerialPort *port);
    void setToolTip(const QSerialPort *port);
};

#endif // STATUSBAR_H
