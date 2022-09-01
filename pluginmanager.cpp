#include "pluginmanager.h"

#define TRACE                                                                                                          \
    if (!debug) {                                                                                                      \
    } else                                                                                                             \
        qDebug()
static bool debug = false;

PluginManager::PluginManager(QFrame *parent, QVBoxLayout *layout, Settings *settings)
    : m_parent(parent)
    , m_layout(layout)
    , m_settings(settings)
{
}

PluginManager::~PluginManager()
{
    QListIterator<Plugin *> i(m_list);
    while (i.hasNext()) {
        Plugin *item = static_cast<Plugin *>(i.next());
        if (item)
            removePlugin(item);
    }
}

/**
 * @brief [SLOT] Add a new plugin and initialize it depending its type
 * @param type Supported plugin type (see: en_plugin_type)
 */
void PluginManager::addPluginType(en_plugin_type type)
{
    TRACE << "[PluginManager] Adding new plugin: " << type;
    if (type == en_plugin_type::PLUGIN_TYPE_MACROS) {
        /* specific plugin initialization */
        MacroPlugin *macro = new MacroPlugin(m_parent, m_settings);
        connect(macro, &MacroPlugin::unload, this, &PluginManager::removePlugin);
        connect(macro, &MacroPlugin::sendCmd, this, &PluginManager::sendCmd);
        /* common plugin initialization */
        addPlugin(static_cast<Plugin *>(macro->plugin()));
    } else if (type == en_plugin_type::PLUGIN_TYPE_NET_PROXY) {
        NetProxyPlugin *proxy = new NetProxyPlugin(m_parent, m_settings);
        connect(proxy, &NetProxyPlugin::unload, this, &PluginManager::removePlugin);
        connect(proxy, &NetProxyPlugin::sendCmd, this, &PluginManager::sendCmd);
        connect(this, &PluginManager::recvCmd, proxy, &NetProxyPlugin::proxyCmd);
        /* common plugin initialization */
        addPlugin(static_cast<Plugin *>(proxy->plugin()));
    } else if (type == en_plugin_type::PLUGIN_TYPE_BYTE_COUNTER) {
        CounterPlugin *counter = new CounterPlugin(m_parent, m_settings);
        connect(counter, &CounterPlugin::unload, this, &PluginManager::removePlugin);
        connect(this, &PluginManager::recvCmd, counter, &CounterPlugin::rxBytes);
        /* common plugin initialization */
        addPlugin(static_cast<Plugin *>(counter->plugin()));
    }
}

/**
 * @brief [SLOT] Remove an existing plugin
 * @param plugin A pointer to the plugin to delete
 */
void PluginManager::removePlugin(Plugin *plugin)
{
    TRACE << "[PluginManager] Removing plugin: " << plugin->name;
    if (!plugin)
        return;

    if (plugin->frame) {
        plugin->frame->close();
    }
    plugin->deleteLater();
    m_list.removeOne(plugin);
    plugin = nullptr;
}

/**
 * @brief Adds a plugin in the manager list and also does the
 *  additional initialization
 * @param item The plugin to add
 */
void PluginManager::addPlugin(Plugin *item)
{
    if (!item)
        return;

    m_list.append(item);
    /* if the plugin has also a frame then add it */
    if (item->frame) {
        QMargins mainMargins = m_layout->contentsMargins();
        item->frame->setContentsMargins(mainMargins);
        m_layout->addWidget(item->frame);
        item->frame->show();
    }
    TRACE << "[PluginManager] Added new plugin: " << item->name;
}

/**
 * @brief Inject and process the cmd data before they sent
 * @param cmd The data
 */
void PluginManager::processCmd(QString *cmd)
{
    TRACE << "[PluginManager] process: " << *cmd;
    QListIterator<Plugin *> i(m_list);
    while (i.hasNext()) {
        Plugin *item = static_cast<Plugin *>(i.next());
        if (item->processCmd) {
            QString new_cmd;
            if (item->processCmd(cmd, &new_cmd)) {
                TRACE << "[PluginManager::processCmd]: " << cmd->toLatin1();
                *cmd = new_cmd;
            }
        }
    }
}
