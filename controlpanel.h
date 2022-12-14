#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "settings.h"
#include "ui_controlpanel.h"

#include <QFrame>
#include <QSerialPort>

class ControlPanel : public QFrame, public Ui::ControlPanel
{
    Q_OBJECT

    friend class MainWindow;

signals:
    void openDeviceClicked();
    void closeDeviceClicked();
    void settingChanged(Settings::Options option, QVariant setting);

public:
    explicit ControlPanel(QWidget *parent = nullptr, Settings *settings = nullptr);
    ~ControlPanel();
    /**
     * Returns the space in the y-achsis needed
     * when the panel is collapsed
     * @brief hiddenHeight
     * @return
     */
    int hiddenHeight() { return height() + m_y; }
    void collapse();
    void resize(int w, int h);
    void slideOut();
    /**
     * @brief setLeftMargin
     * @param x
     */
    void setLeftMargin(int x) { m_x = x; }

    void fillDeviceCombo(const QString &deviceName);
    void applySessionSettings(Settings::Session settings);

    void closeDevice()
    {
        toggleDevice(false);
        m_bt_open->setChecked(false);
    }

private:
    void fillBaudCombo();
    void fillFlowCombo();
    void fillParityCombo();
    void fillDataBitCombo();
    void fillStopBitCombo();
    void fillOpenModeCombo();

    // slots
    void tabClicked(int i)
    {
        Q_UNUSED(i);
        toggleMenu();
    }
    void toggleMenu();
    void toggleDevice(bool open);
    void customBaudRate(int index);
    void customBaudRateSet();
    void chooseLogFile();

    /**
     * @brief   Designed to catch QComboBox::currentIndexChanged(int) signal. Its roles is to set the
     *          proper visibility of RTS and DTR checkboxes which depends on selected type of flow control.
     *          If user selects the hardware flow control, then RTS and DTR checkboxes are being invisible.
     *          If user selects none or software flow control, then RTS and DTR checkboxes are being visible.
     * @param   index   QComboBox item's index.
     */
    void changeVisibilityOfRTSandDTRCheckboxes(int index);

private:
    int m_x;
    int m_y;
    bool m_menuVisible;
    QIntValidator *m_baudValidator;
    QLineEdit *m_baud_edit;
    QIcon showIcon;
    QIcon hideIcon;
};

#endif // CONTROLPANEL_H
