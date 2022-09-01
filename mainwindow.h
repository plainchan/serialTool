#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controlpanel.h"
#include "ctrlcharacterspopup.h"
#include "pluginmanager.h"
#include "sessionmanager.h"
#include "settings.h"
#include "statusbar.h"
#include "ui_mainwindow.h"

#include <QFont>
#include <QMainWindow>
#include <QProgressDialog>
#include <QPropertyAnimation>
#include <QtSerialPort/QSerialPort>

class MainWindow : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

    enum DeviceState { DEVICE_CLOSED, DEVICE_OPENING, DEVICE_OPEN, DEVICE_CLOSING, DEVICE_RECONNECT };

public:
    explicit MainWindow(QWidget *parent = nullptr, const QString &session = "");
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    void openDevice();
    void closeDevice();
    void processData();
    void handleError(QSerialPort::SerialPortError);
    void printDeviceInfo();
    void showAboutMsg();
    void setHexOutputFormat(bool checked);
    void saveCommandHistory();
    void disableInput();

private slots:
    /**
     * @brief Action to handle QAction::triggered signal. It removes selected items from inputs history list.
     */
    void removeSelectedInputItems();

protected:
    void prevCmd();
    void nextCmd();
    void execCmd();
    void commandFromHistoryClicked(QListWidgetItem *item);
    bool sendString(QString *s);
    bool sendByte(const char c, unsigned long delay);
    void sendKey();
    void sendFile();
    void readFromStdErr();
    void sendDone(int exitCode, QProcess::ExitStatus exitStatus);
    void closeEvent(QCloseEvent *event);

protected slots:
    /**
     * @brief Handles QCheckBox::stateChanged signal received from RTS checkbox (placed in control panel).
     */
    void setRTSLineState(int checked);

    /**
     * @brief Handles QCheckBox::stateChanged signal received from DTR checkbox (placed in control panel).
     */
    void setDTRLineState(int checked);

private:
    void toggleLogging(bool start);
    void fillLineTerminationChooser(const Settings::LineTerminator setting = Settings::LF);
    void fillProtocolChooser(const Settings::Protocol setting = Settings::PLAIN);
    void killSz();
    void switchSession(const QString &session);
    void updateCommandHistory();

    ControlPanel *controlPanel;
    SessionManager *m_sessionManager;
    PluginManager *m_plugin_manager;
    QSerialPort *m_device;
    DeviceState m_deviceState;
    StatusBar *m_device_statusbar;
    Settings *m_settings;
    QProgressDialog *m_progress;
    int m_progressStepSize;
    QProcess *m_sz;
    bool m_devices_needs_refresh;
    char m_previousChar;
    QTime m_timestamp;
    QFile m_logFile;

    QCompleter *m_commandCompleter;
    QStringListModel *m_command_history_model;
    QMenu *m_command_history_menu;

    /// @brief Popup widget that provides graphical way to enter ASCII control characters into input field.
    popup_widget::CtrlCharactersPopup *m_ctrlCharactersPopup;

    /**
     * @brief m_keyRepeatTimer
     */
    QTimer m_keyRepeatTimer;
    char m_keyCode;

    /**
     * @brief m_cmdBufIndex
     */
    int m_cmdBufIndex;

    QTimer m_reconnectTimer;
};

#endif // MAINWINDOW_H
