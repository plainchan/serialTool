#include "macroplugin.h"
#include "ui_macroplugin.h"

#define TRACE                                                                                                          \
    if (!debug) {                                                                                                      \
    } else                                                                                                             \
        qDebug()

static bool debug = false;

MacroPlugin::MacroPlugin(QFrame *parent, Settings *settings)
    : QFrame(parent)
    , ui(new Ui::MacroPlugin)
    , m_settings(settings)
{
    ui->setupUi(this);
    /* Plugin by default disabled, no injection, has QFrame, no injection process cmd */
    m_plugin = new Plugin(this, "Macros", this);

    /* Array of buttons that belongs to the frame that is displayed in the main
     * dialog. Because we want to handle these buttons the same way that we handle
     * the buttons from the macro dialog, then we pass that pointer to the dialog
     * and we handle all buttons there.
     */
    QPushButton **macro_buttons = new QPushButton *[MacroSettings::NUM_OF_BUTTONS] {
        ui->m_bt_macro_1, ui->m_bt_macro_2, ui->m_bt_macro_3, ui->m_bt_macro_4, ui->m_bt_macro_5, ui->m_bt_macro_6,
            ui->m_bt_macro_7, ui->m_bt_macro_8, ui->m_bt_macro_9, ui->m_bt_macro_10, ui->m_bt_macro_11,
            ui->m_bt_macro_12, ui->m_bt_macro_13, ui->m_bt_macro_14, ui->m_bt_macro_15, ui->m_bt_macro_16,
    };
    /* Create the macro dialog */
    m_macroSettings = new MacroSettings(macro_buttons, this);
    /* Load the macro settings file that is pointed in the current session */
    m_macroSettings->loadFile(m_settings->getCurrentSession().macroFile);
    /* event to show the macro dialog */
    connect(ui->m_bt_set_macros, &QPushButton::clicked, m_macroSettings, &MacroSettings::show);
    /* event for when session changes and a new file needs to be loaded */
    connect(m_macroSettings, &MacroSettings::fileChanged, m_settings, [=]() {
        /* get the new macro settings file */
        m_settings->settingChanged(Settings::MacroFile, m_macroSettings->getMacroFilename());
        /* load file */
        m_macroSettings->loadFile(m_macroSettings->getMacroFilename());
        //        qDebug() << "L1 session: " << m_settings->getCurrentSessionName()
        //                 << ", fname: " << m_macroSettings->getMacroFilename()
        //                 << ", sfname: " << m_settings->getCurrentSession().macroFile;
    });
    /* send serial string */
    connect(m_macroSettings, &MacroSettings::sendCmd, this, &MacroPlugin::sendCmd);
    /* unload */
    connect(ui->m_bt_unload, &QPushButton::clicked, this, &MacroPlugin::removePlugin);
}

MacroPlugin::~MacroPlugin()
{
    TRACE << "[MacroPlugin] ~()";
    delete ui;
}

/**
 * @brief Return a pointer to the plugin data
 * @return
 */
Plugin *MacroPlugin::plugin() { return m_plugin; }

/**
 * @brief [SLOT] Send unload command to the plugin manager
 */
void MacroPlugin::removePlugin(bool) { emit unload(m_plugin); }
