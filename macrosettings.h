#ifndef MACROSETTINGS_H
#define MACROSETTINGS_H

#include "ui_macrosettings.h"
#include <QFileDialog>
#include <QTimer>

class MacroSettings : public QDialog, private Ui::MacroSettings
{
    Q_OBJECT

public:
    enum { NUM_OF_BUTTONS = 16 };
    explicit MacroSettings(QPushButton **mainButtons, QWidget *parent = nullptr);
    virtual ~MacroSettings();
    void showPanel(bool setVisible);
    QString getMacroFilename(void) { return m_macroFilename; }
    void loadFile(QString fname);

public slots:
    void macroPress();

protected slots:
    void openFile();
    void saveFile();

signals:
    void closing();
    void sendCmd(QByteArray);
    void fileChanged(QString);

private:
    struct macro_item {
        macro_item() = default;
        macro_item(QLineEdit *cmd, QLineEdit *name, QSpinBox *tmr_interval, QPushButton *button, QCheckBox *tmr_active,
                   QTimer *tmr)
            : cmd(cmd)
            , name(name)
            , tmr_interval(tmr_interval)
            , button(button)
            , tmr_active(tmr_active)
            , tmr(tmr)
        {
        }
        QLineEdit *cmd;
        QLineEdit *name;
        QSpinBox *tmr_interval;
        QPushButton *button;
        QCheckBox *tmr_active;
        QTimer *tmr;
    };
    int getButtonIndex(QString btnName);
    bool parseFile(QTextStream &in);
    QWidget *m_mainForm;
    QString m_macroFilename;
    struct macro_item **m_macros;
    void helpMsg(void);
};

#endif // MACROSETTINGS_H
