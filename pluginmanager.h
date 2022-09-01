#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "counterplugin.h"
#include "macroplugin.h"
#include "netproxyplugin.h"
#include "plugin.h"
#include "settings.h"
#include <QDebug>
#include <QFrame>
#include <QObject>
#include <QVBoxLayout>

class PluginManager : public QObject
{
    Q_OBJECT

public:
    /* Every plug in has its own type */
    enum en_plugin_type {
        PLUGIN_TYPE_MACROS,
        PLUGIN_TYPE_NET_PROXY,
        PLUGIN_TYPE_BYTE_COUNTER,
    };
    PluginManager(QFrame *parent, QVBoxLayout *layout, Settings *settings);
    virtual ~PluginManager();
    void processCmd(QString *text);

public slots:
    void addPluginType(en_plugin_type);
    void removePlugin(Plugin *);

signals:
    void recvCmd(QByteArray); /* mainwindow -> manager */
    void sendCmd(QByteArray); /* manager -> mainwindow */

protected:
    void addPlugin(Plugin *item);

private:
    QFrame *m_parent;
    QVBoxLayout *m_layout;
    QList<Plugin *> m_list;
    Settings *m_settings;
    /* Supported plugins */
    MacroPlugin *m_macro_plugin;
};
#endif // PLUGINMANAGER_H
