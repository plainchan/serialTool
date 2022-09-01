#ifndef DEVICECOMBO_H
#define DEVICECOMBO_H

#include <QComboBox>

class DeviceCombo : public QComboBox
{
    Q_OBJECT

public:
    DeviceCombo(QWidget *parent = nullptr)
        : QComboBox(parent)
    {
    }

    virtual void showPopup() Q_DECL_OVERRIDE;

private:
    void refill();
};

#endif // DEVICECOMBO_H
