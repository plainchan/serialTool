#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include "settings.h"
#include "ui_sessionmanager.h"

#include <QItemDelegate>

class SessionManager : public QDialog, private Ui::SessionManager
{
    Q_OBJECT

signals:
    void sessionSwitched(const QString &name);
    void sessionRemoved(const QString &name);
    void sessionRenamed(const QString &source, const QString &destination);
    void sessionCloned(const QString &source, const QString &destination);

public:
    explicit SessionManager(Settings *settings, QWidget *parent = nullptr);
    void editingFinished(const QString &newSessionName);

private:
    void currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void switchSession();
    void removeSession();
    void cloneSession();
    void renameSession();

    /**
     * stores the reference of the application wide settings instance
     * @brief m_settings
     */
    Settings *m_settings;
    /**
     * The currently selected session
     * @brief m_current_item
     */
    QListWidgetItem *m_current_item;
    /**
     * The currently used session
     * @brief m_current_item
     */
    QListWidgetItem *m_current_session;

    bool m_isCloning;
    bool m_isRenaming;
    QString m_previous_sessionName;
};

class SessionItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    SessionItemDelegate(QListWidget *list)
        : QItemDelegate(list)
        , m_list(list)
    {
    }
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const Q_DECL_OVERRIDE;

signals:
    void editingFinished(QString newSessionName) const;

private:
    QListWidget *m_list;
};

#endif // SESSIONMANAGER_H
