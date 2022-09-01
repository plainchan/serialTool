#ifndef MACROPLUGIN_H
#define MACROPLUGIN_H

#include "macrosettings.h"
#include "plugin.h"
#include "settings.h"
#include <QDebug>
#include <QFrame>

namespace Ui
{
class MacroPlugin;
}

class MacroPlugin : public QFrame
{
    Q_OBJECT

public:
    explicit MacroPlugin(QFrame *parent, Settings *settings);
    virtual ~MacroPlugin();
    Plugin *plugin();
    int processCmd(const QString *text);

signals:
    void sendCmd(QByteArray);
    void unload(Plugin *);

public slots:
    void removePlugin(bool);

private:
    Ui::MacroPlugin *ui;
    Plugin *m_plugin;
    MacroSettings *m_macroSettings;
    Settings *m_settings;
};

#endif // MACROPLUGIN_H
